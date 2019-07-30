/*
 * oracle_statement.cpp
 *
 *  Created on: 2018-2-6
 *      Author: xiaoba-8
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <mix/database/db_errno.h>
#include "stringutil.h"
#include <mix/oracle/oracle_statement.h>
#include <mix/oracle/oracle_connection.h>
#include <mix/oracle/oracle_result_set.h>

namespace mix
{

oracle_statement::oracle_statement(oracle_connection *pConn,
		oracle::occi::Statement *pStatement, std::string charset) :
	m_pConn(pConn), m_pStatement(pStatement), m_charset(charset)
{
	m_closed = false;
}

oracle_statement::~oracle_statement()
{
	try
	{
		Close();
	}
	catch (mix::sql_exception &e)
	{
	}

	ClearMap();
}

void oracle_statement::ClearMap()
{
	std::map<unsigned int, Lob *>::iterator itr = m_lobValMap.begin();

	for (; itr != m_lobValMap.end(); ++itr)
	{
		delete (*itr).second;
	}

	m_lobValMap.clear();
	m_lobTypeMap.clear();
}

void oracle_statement::SetAutoCommit(bool bAutoCommit)
{
	m_pConn->SetAutoCommit(bAutoCommit);
	m_pStatement->setAutoCommit(bAutoCommit);
}

bool oracle_statement::GetAutoCommit()
{
	return m_pStatement->getAutoCommit();
}

void oracle_statement::Commit()
{
	m_pConn->GetConnection()->commit();
}

void oracle_statement::Rollback()
{
	m_pConn->GetConnection()->rollback();
}

void oracle_statement::Close()
{
	try
	{
		if (!m_closed)
		{
			m_pConn->GetConnection()->terminateStatement(m_pStatement);
			m_pConn->SetStatement(NULL);
			m_closed = true;
		}
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_STATEMENT_CLOSE, "oracle_statement::Close:%s", e.what());
	}
}

i_result_set *oracle_statement::ExecuteQuery(std::string sql) throw (sql_exception)
{
	if (this->m_pConn->IsClosed())
		throw sql_exception(DATABASE_CLOSED, "oracle_statement: Connection Closed!");

	try
	{
		return new oracle_result_set(this, m_pStatement, m_pStatement->executeQuery(sql), m_charset);
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_QUERY, "oracle_statement::ExecuteQuery:%s : %s", e.what(), sql.c_str());
	}
}

int oracle_statement::ExecuteUpdate(std::string sql) throw (sql_exception)
{
	if (this->m_pConn->IsClosed())
		throw sql_exception(DATABASE_CLOSED, "oracle_statement: Connection Closed!");

	try
	{
		return m_pStatement->executeUpdate(sql);
		//		return m_pStatement->getUpdateCount();
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_UPDATE, "oracle_statement::ExecuteUpdate:%s : %s", e.what(), sql.c_str());
	}
}

i_result_set *oracle_statement::ExecuteQuery() throw (sql_exception)
{
	if (this->m_pConn->IsClosed())
		throw sql_exception(DATABASE_CLOSED, "oracle_statement: Connection Closed!");

	try
	{
		return new oracle_result_set(this, m_pStatement, m_pStatement->executeQuery(), m_charset);
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_QUERY, "oracle_statement::ExecuteQuery:%s : %s", e.what(), m_pStatement->getSQL().c_str());
	}
}

int oracle_statement::ExecuteUpdate() throw (sql_exception)
{
	if (this->m_pConn->IsClosed())
		throw sql_exception(DATABASE_CLOSED, "oracle_statement: Connection Closed!");

	int nRet = 0;
	try
	{
		if (m_lobValMap.size() > 0)
		{
			std::string sql = ora::toUpcase(
					m_pStatement->getSQL());

			if (ora::startWith(sql, "INSERT "))
			{
				std::map<unsigned int, enum LobType>::iterator itr =
						m_lobTypeMap.begin();

				for (; itr != m_lobTypeMap.end(); ++itr)
				{
					unsigned int index = (*itr).first;
					enum LobType lt = (*itr).second;

					Lob *pLob = m_lobValMap[index];
					pLob->SetNeedUpdate(true);

					switch (lt)
					{
					case BLOB:
					{
						oracle::occi::Blob blob(m_pConn->GetConnection());
						blob.setEmpty();
						m_pStatement->setBlob(index, blob);
						break;
					}
					case CLOB:
					{
						oracle::occi::Clob clob(m_pConn->GetConnection());
						clob.setEmpty();
						m_pStatement->setClob(index, clob);
						break;
					}
					}
				}

				nRet = m_pStatement->executeUpdate();
			}
			else if (ora::startWith(sql, "SELECT ")
					&& ora::endWith(sql, "FOR UPDATE"))
			{
				oracle::occi::ResultSet *rs = m_pStatement->executeQuery();

				if (rs->next() != oracle::occi::ResultSet::END_OF_FETCH)
				{
					std::map<unsigned int, enum LobType>::iterator itr =
							m_lobTypeMap.begin();
					for (; itr != m_lobTypeMap.end(); ++itr)
					{
						m_lobValMap[(*itr).first]->SetNeedUpdate(false);

						switch ((*itr).second)
						{
						case BLOB:
						{
							oracle::occi::Blob blob = rs->getBlob((*itr).first);
							char buffer[1024];

							Lob *pLob = m_lobValMap[(*itr).first];
							std::istream *x = pLob->GetStream();


							blob.open(oracle::occi::OCCI_LOB_WRITEONLY);

							int offset = 1;
							if (x != NULL)
							{
								while (!x->eof())
								{
									x->read(buffer, 1024);
									unsigned int n = x->gcount();

									if (n == 0) break;

									blob.writeChunk(n, (unsigned char *) buffer, n, offset);
									offset += n;
								}
							}
							blob.close();

							break;
						}
						case CLOB:
						{
							oracle::occi::Clob clob = rs->getClob((*itr).first);
							char buffer[1024];

							Lob *pLob = m_lobValMap[(*itr).first];
							std::istream *x = pLob->GetStream();

							clob.open(oracle::occi::OCCI_LOB_WRITEONLY);
							int offset = 1;
							while (!x->eof())
							{
								x->read(buffer, 1024);
								unsigned int n = x->gcount();

								if (n == 0) break;

								clob.writeChunk(n, (unsigned char *) buffer, n, offset);
								offset += n;
							}

							clob.close();

							break;
						}
						}
					}
				}

				ClearMap();
			}
			else if (ora::startWith(sql, "UPDATE "))
			{
				std::map<unsigned int, enum LobType>::iterator itr =
						m_lobTypeMap.begin();

				for (; itr != m_lobTypeMap.end(); ++itr)
				{
					m_lobValMap[(*itr).first]->SetNeedUpdate(true);

					switch ((*itr).second)
					{
					case BLOB:
					{
						oracle::occi::Blob blob(m_pConn->GetConnection());
						blob.setEmpty();
						m_pStatement->setBlob((*itr).first, blob);
						break;
					}
					case CLOB:
					{
						oracle::occi::Clob clob(m_pConn->GetConnection());
						clob.setEmpty();
						m_pStatement->setClob((*itr).first, clob);
						break;
					}
					}
				}

				nRet = m_pStatement->executeUpdate();
			}
		}
		else
		{
			nRet = m_pStatement->executeUpdate();
		}
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_UPDATE, "oracle_statement::ExecuteQuery:%s : %s", e.what(), m_pStatement->getSQL().c_str());
	}

	return nRet;
}

int oracle_statement::GetQueryTimeout()
{
	throw sql_exception(DATABASE_NOTSUPPORT, "Not supported yet");
}

void oracle_statement::SetQueryTimeout(long)
{
	throw sql_exception(DATABASE_NOTSUPPORT, "Not supported yet");
}

bool oracle_statement::Execute(std::string sql) throw (sql_exception)
{
	if (this->m_pConn->IsClosed())
		throw sql_exception(DATABASE_CLOSED, "oracle_statement: Connection Closed!");

	try
	{
		return m_pStatement->execute(sql);
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_UPDATE, "oracle_statement::ExecuteQuery:%s : %s", e.what(), sql.c_str());
	}
}

i_result_set *oracle_statement::GetResultSet()
{
	return new oracle_result_set(this, m_pStatement, m_pStatement->getResultSet(), m_charset);
}

int oracle_statement::GetUpdateCount()
{
	return m_pStatement->getUpdateCount();
}

int oracle_statement::GetFetchSize()
{
	throw sql_exception(DATABASE_NOTSUPPORT, "Not supported");
}

void oracle_statement::SetFetchSize(int size)
{
	m_pStatement->setPrefetchRowCount(size);
}

void oracle_statement::SetNull(unsigned int paramIndex, int type)
{
	m_pStatement->setNull(paramIndex, static_cast<oracle::occi::Type> (type));
}

void oracle_statement::SetInt(unsigned int paramIndex, Integer x)
{
	if (x.IsNull())
		m_pStatement->setNull(paramIndex, oracle::occi::OCCIINT);
	else
		m_pStatement->setInt(paramIndex, x);
}

void oracle_statement::SetUInt(unsigned int paramIndex, UInteger x)
{
	if (x.IsNull())
		m_pStatement->setNull(paramIndex, oracle::occi::OCCIINT);
	else
		m_pStatement->setUInt(paramIndex, x);
}

void oracle_statement::SetUInt64(unsigned int paramIndex, UInt64 x)
{
	if (x.IsNull())
		m_pStatement->setNull(paramIndex, oracle::occi::OCCIINT);
	else
	{
		oracle::occi::Number uintx(8);
		char buffer[32];
		sprintf(buffer, "%llu", x.Value());
		uintx.fromText(m_pConn->GetCreater()->GetEnvironment(), buffer, "999999999999999999999");//(static_cast<unsigned long>(x.Value()));
		m_pStatement->setNumber(paramIndex, uintx);
	}
}

void oracle_statement::SetFloat(unsigned int paramIndex, Float x)
{
	if (x.IsNull())
		m_pStatement->setNull(paramIndex, oracle::occi::OCCIFLOAT);
	else
		m_pStatement->setFloat(paramIndex, x);
}

void oracle_statement::SetDouble(unsigned int paramIndex, Double x)
{
	if (x.IsNull())
		m_pStatement->setNull(paramIndex, oracle::occi::OCCIDOUBLE);
	else
		m_pStatement->setDouble(paramIndex, x);
}

void oracle_statement::SetString(unsigned int paramIndex, const std::string &x)
{
	if (x.empty())
		m_pStatement->setNull(paramIndex, oracle::occi::OCCISTRING);
	else
		m_pStatement->setString(paramIndex, x);
}

void oracle_statement::SetCharSet(unsigned int paramIndex,
		const std::string & charSet)
{
	return m_pStatement->setCharSet(paramIndex, charSet);
}

std::string oracle_statement::GetCharSet(unsigned int paramIndex) const
{
	return m_pStatement->getCharSet(paramIndex);
}

int oracle_statement::GetInt(unsigned int paramIndex)
{
	return m_pStatement->getInt(paramIndex);
}

unsigned int oracle_statement::GetUInt(unsigned int paramIndex)
{
	return m_pStatement->getUInt(paramIndex);
}

float oracle_statement::GetFloat(unsigned int paramIndex)
{
	return m_pStatement->getFloat(paramIndex);
}

double oracle_statement::GetDouble(unsigned int paramIndex)
{
	return m_pStatement->getDouble(paramIndex);
}

std::string oracle_statement::GetString(unsigned int paramIndex)
{
	return m_pStatement->getString(paramIndex);
}

void oracle_statement::SetDate(unsigned int paramIndex, const Date &x)
{
	if (x.IsNull())
		m_pStatement->setNull(paramIndex, oracle::occi::OCCIDATE);
	else
	{
		int year;
		unsigned int month;
		unsigned int day;
		unsigned int hour;
		unsigned int minute;
		unsigned int second;

		x.GetLocalDate(year, month, day, hour, minute, second);

		oracle::occi::Date oDate(m_pConn->GetCreater()->GetEnvironment(),
				year - 1900, month, day, hour, minute, second);
		m_pStatement->setDate(paramIndex, oDate);
	}
}

void oracle_statement::SetTimestamp(unsigned int paramIndex, const Timestamp &x)
{
	if (x.IsNull())
		m_pStatement->setNull(paramIndex, oracle::occi::OCCITIMESTAMP);
	else
	{
		int year;
		unsigned int month;
		unsigned int day;
		unsigned int hour;
		unsigned int minute;
		unsigned int second;
		unsigned int fs = 0;

		x.GetLocalDate(year, month, day);
		x.GetLocalTime(hour, minute, second, fs);

		oracle::occi::Timestamp oTimestamp(m_pConn->GetCreater()->GetEnvironment(),
				year, month, day, hour, minute, second, fs);

		m_pStatement->setTimestamp(paramIndex, oTimestamp);
	}
}

void oracle_statement::SetBlob(unsigned int paramIndex, Blob &x)
{
	m_lobValMap[paramIndex] = new Blob(x);
	m_lobTypeMap[paramIndex] = BLOB;
}

void oracle_statement::SetClob(unsigned int paramIndex, Clob &x)
{
	m_lobValMap[paramIndex] = new Clob(x);
	m_lobTypeMap[paramIndex] = CLOB;
}

Date oracle_statement::GetDate(unsigned int paramIndex)
{
	int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;

	oracle::occi::Date oDate = m_pStatement->getDate(paramIndex);

	if (oDate.isNull())
	{
		oDate.getDate(year, month, day, hour, minute, second);
		return Date(year, month, day, hour, minute, second);
	}
	else
	{
		Date dt;
		dt.SetNull();
		return dt;
	}
}

Timestamp oracle_statement::GetTimestamp(unsigned int paramIndex)
{
	int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	unsigned int fs = 0;

	oracle::occi::Timestamp oTimestamp = m_pStatement->getTimestamp(paramIndex);

	if (oTimestamp.isNull())
	{
		Timestamp ts;
		ts.SetNull();
		return ts;
	}
	else
	{
		oTimestamp.getDate(year, month, day);
		oTimestamp.getTime(hour, minute, second, fs);

		return Timestamp(year, month, day, hour, minute, second, fs);
	}
}

void oracle_statement::SetSQL(const std::string &sql)
{
	int i = 1;
	std::string::size_type pos = 0;
	std::string lSql = sql;
	ora::trim(lSql);

	while ((pos = lSql.find('?', pos)) != std::string::npos)
	{
		std::stringstream ss;
		ss << ":" << i++;
		lSql.replace(pos, 1, ss.str());
	}

	try
	{
		m_pStatement->setSQL(lSql);
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_UPDATE, "oracle_statement::SetSQL:%s : %s", e.what(), sql.c_str());
	}
}

bool oracle_statement::NeedUpdateBlob()
{
	if (m_lobValMap.size() > 0)
		return true;
	return false;
}

}
