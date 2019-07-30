/*
 * oracle_connection.cpp
 *
 *  Created on: 2018-2-6
 *      Author: xiaoba-8
 */

#include <mix/database/db_errno.h>
#include <mix/oracle/oracle_creater.h>
#include <mix/oracle/oracle_connection.h>
#include <mix/oracle/oracle_statement.h>

namespace mix
{

oracle_connection::oracle_connection(i_ora_creater *pCreater,
		oracle::occi::Connection *pConn, std::string dbname, unsigned long int threadId, std::string charset) :
	m_pCreater(pCreater), m_pConn(pConn), m_pStatement(NULL), m_dbname(dbname), m_threadId(threadId),
	m_charset(charset), m_bAutoCommit(true), m_bClosed(false)
{

}

oracle_connection::oracle_connection(oracle_connection &orig) :
	m_pCreater(orig.m_pCreater), m_pConn(orig.m_pConn), m_pStatement(orig.m_pStatement),
	m_dbname(orig.m_dbname), m_threadId(orig.m_threadId),
	m_charset(orig.m_charset), m_bClosed(false)
{

}

oracle_connection::~oracle_connection()
{
	try
	{
		if (m_pStatement != NULL)
		{
			m_pConn->terminateStatement(m_pStatement);
			m_pStatement = NULL;
		}
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_CONNECTION_DESTROY, "oracle_connection::TerminateConnection : %s", e.what());
	}
}

oracle::occi::Statement *oracle_connection::GetStatement()
{
	try
	{
		if (m_pStatement == NULL)
		{
			m_pStatement = m_pConn->createStatement();
			m_pStatement->setAutoCommit(m_bAutoCommit);
		}

		return m_pStatement;
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_CONNECTION_CREATE, "oracle_connection::CreateConnection : %s", e.what());
	}
}

i_statement *oracle_connection::CreateStatement() throw (sql_exception)
{
	if (this->m_bClosed)
		throw sql_exception(DATABASE_CLOSED, "oracle_connection: Connection Closed!");

	try
	{
		return new oracle_statement(this, GetStatement(), m_charset);
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_STATEMENT_CREATE, "oracle_connection::CreateStatement : %s", e.what());
	}
}

i_prepared_statement *oracle_connection::PrepareStatement(std::string sql) throw (sql_exception)
{
	if (this->m_bClosed)
		throw sql_exception(DATABASE_CLOSED, "oracle_connection: Connection Closed!");

	try
	{
		oracle_statement *pStatement = (oracle_statement *)CreateStatement();
		pStatement->SetSQL(sql);

		return pStatement;
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_PRESTATEMENT_CREATE, "oracle_connection::PrepareStatement : %s", e.what());
	}
}

void oracle_connection::SetAutoCommit(bool bAutoCommit)
{
	if (m_pStatement != NULL)
		m_pStatement->setAutoCommit(bAutoCommit);
	m_bAutoCommit = bAutoCommit;
}

bool oracle_connection::GetAutoCommit()
{
	return m_bAutoCommit;
}

void oracle_connection::Commit()
{
	try
	{
		m_pConn->commit();
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_TRANSACTION_COMMIT, "oracle_connection::Commit : %s", e.what());
	}
}

void oracle_connection::Rollback()
{
	try
	{
		m_pConn->rollback();
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_TRANSACTION_ROLLBACK, "oracle_connection::Rollback : %s", e.what());
	}
}

void oracle_connection::Close()
{
	if (m_pStatement != NULL)
	{
		m_pConn->terminateStatement(m_pStatement);
		m_pStatement = NULL;
	}
	m_pCreater->TerminateConnection(new oracle_connection(*this));
	m_pConn = NULL;
}

std::string oracle_connection::GetDbname()
{
	return m_dbname;
}

unsigned long int oracle_connection::GetThreadId()
{
	return m_threadId;
}

void oracle_connection::SetThreadId(unsigned long int threadId)
{
	m_threadId = threadId;
}

oracle::occi::Connection *oracle_connection::GetConnection()
{
	return m_pConn;
}

void oracle_connection::SetStatement(oracle::occi::Statement *pStmt)
{
	m_pStatement = pStmt;
}

i_ora_creater *oracle_connection::GetCreater()
{
	return m_pCreater;
}

bool oracle_connection::IsClosed()
{
	return m_bClosed;
}

void oracle_connection::SetClose()
{
	m_bClosed = true;
}

}
