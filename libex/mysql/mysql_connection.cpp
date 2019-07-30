/*
 * mysql_connection.cpp
 *
 *  Created on: 2018-2-6
 *      Author: xiaoba-8
 */

#include <mix/database/db_errno.h>

#include <mix/mysql/mysql_connection.h>
#include <mix/mysql/mysql_statement.h>
#include <mix/mysql/mysql_prepared_statement.h>

namespace mix
{

mysql_connection::mysql_connection(i_creater *pCreater,
		sql::Connection *pConn, std::string dbname, unsigned long int threadId) :
	m_pCreater(pCreater), m_pConn(pConn), m_dbname(dbname), m_threadId(threadId), m_bClosed(false)
{

}

mysql_connection::~mysql_connection()
{
}

i_statement *mysql_connection::CreateStatement() throw (sql_exception)
{
	try
	{
		i_statement *pStatement = new mysql_statement(m_pConn,
				m_pConn->createStatement());
		return pStatement;
	}
	catch (sql::SQLException &e)
	{
		throw sql_exception(DATABASE_CONNECTION_CREATE, "mysql_connection::CreateStatement : %s", e.what());
	}
}

i_prepared_statement *mysql_connection::PrepareStatement(std::string sql) throw (sql_exception)
{
	try
	{
		i_prepared_statement *pStatement = new mysql_prepared_statement(m_pConn, m_pConn->prepareStatement(sql));
		return pStatement;
	}
	catch (sql::SQLException &e)
	{
		throw sql_exception(DATABASE_PRESTATEMENT_CREATE, "mysql_connection::PrepareStatement : %s", e.what());
	}
}

void mysql_connection::SetAutoCommit(bool bAutoCommit)
{
	m_pConn->setAutoCommit(bAutoCommit);
}

bool mysql_connection::GetAutoCommit()
{
	return true;
}

void mysql_connection::Commit()
{
	m_pConn->commit();
}

void mysql_connection::Rollback()
{
	m_pConn->rollback();
}

void mysql_connection::Close()
{
	m_pConn->close();
}

std::string mysql_connection::GetDbname()
{
	return m_dbname;
}

unsigned long int mysql_connection::GetThreadId()
{
	return m_threadId;
}

void mysql_connection::SetThreadId(unsigned long int threadId)
{
	m_threadId = threadId;
}

sql::Connection *mysql_connection::GetConnection()
{
	return m_pConn;
}

bool mysql_connection::IsClosed()
{
	return m_bClosed;
}

void mysql_connection::SetClose()
{
	m_bClosed = true;
}
}

