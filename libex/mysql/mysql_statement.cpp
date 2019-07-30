/*
 * mysql_statement.cpp
 *
 *  Created on: 2018-2-6
 *      Author: xiaoba-8
 */

#include <mix/database/db_errno.h>

#include <mix/mysql/mysql_statement.h>
#include <mix/mysql/mysql_result_set.h>

namespace mix
{

mysql_statement::mysql_statement(sql::Connection *pConn,
		sql::Statement *pStatement) :
	m_pConn(pConn), m_pStatement(pStatement)
{
}

mysql_statement::~mysql_statement()
{
	delete m_pStatement;
}

void mysql_statement::SetAutoCommit(bool bAutoCommit)
{
	m_pConn->setAutoCommit(bAutoCommit);
}

bool mysql_statement::GetAutoCommit()
{
	return m_pConn->getAutoCommit();
}

void mysql_statement::Commit()
{
	m_pConn->commit();
}

void mysql_statement::Rollback()
{
	m_pConn->rollback();
}
void mysql_statement::Close()
{
	m_pStatement->close();
}

i_result_set *mysql_statement::ExecuteQuery(std::string sql) throw (sql_exception)
{
	try
	{
		return new mysql_result_set(m_pStatement->executeQuery(sql));
	}
	catch (sql::SQLException &e)
	{
		throw sql_exception(DATABASE_QUERY, "mysql_statement::ExecuteQuery:%s", e.what());
	}
}

int mysql_statement::ExecuteUpdate(std::string sql) throw (sql_exception)
{
	try
	{
		return m_pStatement->executeUpdate(sql);
	}
	catch (sql::SQLException &e)
	{
		throw sql_exception(DATABASE_UPDATE, "mysql_statement::ExecuteUpdate:%s", e.what());
	}
}

int mysql_statement::GetQueryTimeout()
{
	return m_pStatement->getQueryTimeout();
}

void mysql_statement::SetQueryTimeout(long seconds)
{
	m_pStatement->setQueryTimeout(seconds);
}

bool mysql_statement::Execute(std::string sql) throw (sql_exception)
{
	try
	{
		return m_pStatement->execute(sql);
	}
	catch (sql::SQLException &e)
	{
		throw sql_exception(DATABASE_UPDATE, "mysql_statement::Execute:%s", e.what());
	}
}

i_result_set *mysql_statement::GetResultSet()
{
	return new mysql_result_set(m_pStatement->getResultSet());
}

int mysql_statement::GetUpdateCount()
{
	return m_pStatement->getUpdateCount();
}

int mysql_statement::GetFetchSize()
{
	return m_pStatement->getFetchSize();
}

void mysql_statement::SetFetchSize(int size)
{
	m_pStatement->setFetchSize(size);
}

}
