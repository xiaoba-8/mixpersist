/*
 * mysql_prepared_statement.cpp
 *
 *  Created on: 2018-2-6
 *      Author: xiaoba-8
 */

#include <mix/database/db_errno.h>

#include <mix/mysql/mysql_prepared_statement.h>
#include <mix/mysql/mysql_result_set.h>

namespace mix
{

mysql_prepared_statement::mysql_prepared_statement(sql::Connection *pConn,
		sql::PreparedStatement *pStatement) :
		mysql_statement(pConn, pStatement)
{

}

mysql_prepared_statement::~mysql_prepared_statement()
{
}

void mysql_prepared_statement::Close()
{
	(dynamic_cast<sql::PreparedStatement *> (m_pStatement))->close();
}

void mysql_prepared_statement::SetAutoCommit(bool bAutoCommit)
{
	mysql_statement::SetAutoCommit(bAutoCommit);
}

bool mysql_prepared_statement::GetAutoCommit()
{
	return mysql_statement::GetAutoCommit();
}

void mysql_prepared_statement::Commit()
{
	mysql_statement::Commit();
}

void mysql_prepared_statement::Rollback()
{
	mysql_statement::Rollback();
}

i_result_set *mysql_prepared_statement::ExecuteQuery(std::string sql)
		throw (sql_exception)
{
	sql::SQLString sqlString(sql);

	return new mysql_result_set(
			(dynamic_cast<sql::PreparedStatement *> (m_pStatement))->executeQuery(
					sqlString));
}

int mysql_prepared_statement::ExecuteUpdate(std::string sql) throw (sql_exception)
{
	return (dynamic_cast<sql::PreparedStatement *> (m_pStatement))->executeUpdate(
			sql);
//	return m_pStatement->getUpdateCount();
}

int mysql_prepared_statement::GetQueryTimeout()
{
	return mysql_statement::GetQueryTimeout();
}

void mysql_prepared_statement::SetQueryTimeout(long seconds)
{
	mysql_statement::SetQueryTimeout(seconds);
}

bool mysql_prepared_statement::Execute(std::string sql) throw (sql_exception)
{
	return (dynamic_cast<sql::PreparedStatement *> (m_pStatement))->execute(sql);
}

i_result_set *mysql_prepared_statement::GetResultSet()
{
	return mysql_statement::GetResultSet();
}

int mysql_prepared_statement::GetUpdateCount()
{
	return mysql_statement::GetUpdateCount();
}

int mysql_prepared_statement::GetFetchSize()
{
	return mysql_statement::GetFetchSize();
}

void mysql_prepared_statement::SetFetchSize(int size)
{
	mysql_statement::SetFetchSize(size);
}

i_result_set *mysql_prepared_statement::ExecuteQuery() throw (sql_exception)
{
	try
	{
		return new mysql_result_set(
				dynamic_cast<sql::PreparedStatement *> (m_pStatement)->executeQuery());
	}
	catch (sql::SQLException &e)
	{
		throw sql_exception(DATABASE_QUERY, "mysql_prepared_statement::ExecuteQuery:%s", e.what());
	}
}

int mysql_prepared_statement::ExecuteUpdate() throw (sql_exception)
{
	try
	{
		if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
		{
			return dynamic_cast<sql::PreparedStatement *> (m_pStatement)->executeUpdate();
//			return m_pStatement->getUpdateCount();
		}
		else
			return 0;
	} catch (sql::SQLException &e)
	{
		throw sql_exception(DATABASE_UPDATE, "mysql_prepared_statement::ExecuteQuery:%s", e.what());
	}
}

void mysql_prepared_statement::SetNull(unsigned int paramIndex, int type)
{
	if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
		dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setNull(
				paramIndex, type);
}

void mysql_prepared_statement::SetInt(unsigned int paramIndex, Integer x)
{
	if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
	{
		if (x.IsNull())
			dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setNull(
					paramIndex, 4);
		else
			dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setInt(
					paramIndex, x);
	}
}

void mysql_prepared_statement::SetUInt(unsigned int paramIndex, UInteger x)
{
	if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
	{
		if (x.IsNull())
			dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setNull(
					paramIndex, 4);
		else
			dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setUInt(
					paramIndex, x);
	}
}

void mysql_prepared_statement::SetUInt64(unsigned int paramIndex, UInt64 x)
{
	if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
	{
		if (x.IsNull())
			dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setNull(
					paramIndex, 4);
		else
			dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setUInt64(
					paramIndex, x);
	}
}

void mysql_prepared_statement::SetFloat(unsigned int paramIndex, Float x)
{
	if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
	{
		if (x.IsNull())
			dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setNull(
					paramIndex, 6);
		else
			dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setDouble(
					paramIndex, x);
	}
}

void mysql_prepared_statement::SetDouble(unsigned int paramIndex, Double x)
{
	if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
	{
		if (x.IsNull())
			dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setNull(
					paramIndex, 8);
		else
			dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setDouble(
					paramIndex, x);
	}
}

void mysql_prepared_statement::SetString(unsigned int paramIndex,
		const std::string &x)
{
	if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
	{
		dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setString(
				paramIndex, x);
	}
}

void mysql_prepared_statement::SetDate(unsigned int paramIndex, const Date &x)
{
	if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
		dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setInt64(
				paramIndex, x.GetTime());
}

void mysql_prepared_statement::SetTimestamp(unsigned int paramIndex,
		const Timestamp &x)
{
	dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setDateTime(
			paramIndex, x.ToText());

}

void mysql_prepared_statement::SetBlob(unsigned int paramIndex, Blob &x)
{
	if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
		dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setBlob(paramIndex, x.GetStream());
}

void mysql_prepared_statement::SetClob(unsigned int paramIndex, Clob &x)
{
	if (dynamic_cast<sql::PreparedStatement *> (m_pStatement) != NULL)
		dynamic_cast<sql::PreparedStatement *> (m_pStatement)->setBlob(paramIndex, x.GetStream());
}

bool mysql_prepared_statement::NeedUpdateBlob()
{
	return false;
}

}
