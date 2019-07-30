/*
 * oracle_creater.cpp
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#include <mix/database/db_errno.h>
#include <mix/database/database_factory.h>
#include <mix/oracle/oracle_connection.h>
#include <mix/oracle/oracle_creater.h>
#include <mix/database/i_result_set.h>
#include <mix/database/i_prepared_statement.h>

namespace mix
{

void OraInsertSQL(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql)
{
	if (colDef.m_autoincr) return;

	sql_def *pSqlDef = static_cast<sql_def *>(pSql);

	pSqlDef->m_pSql1->append(colDef.m_columnName).append(", ");
	pSqlDef->m_pSql2->append("?, ");

	return;
}

void OraUpdateSQL(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql)
{
	sql_def *pSqlDef = static_cast<sql_def *>(pSql);

	if (colDef.m_identify)
	{
		pSqlDef->m_pSql2->append(colDef.m_columnName).append("=? and ");
	}
	else
	{
		pSqlDef->m_pSql1->append(colDef.m_columnName).append("=?, ");
	}

	return;
}

void OraFindSQL(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql)
{
	sql_def *pSqlDef = static_cast<sql_def *>(pSql);

	pSqlDef->m_pSql1->append(colDef.m_columnName).append(", ");

	if (colDef.m_identify)
	{
		pSqlDef->m_pSql2->append(colDef.m_columnName).append("=? and ");
	}

	return;
}

void OraFindLobForUpdateSQL(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql)
{
	sql_def *pSqlDef = static_cast<sql_def *>(pSql);

	if (colDef.m_identify)
	{
		pSqlDef->m_pSql2->append(colDef.m_columnName).append("=? and ");
	}
	else
	{
		pSqlDef->m_pSql1->append(colDef.m_columnName).append(", ");
	}

	return;
}

void OraDumySQL(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql)
{
	sql_def *pSqlDef = static_cast<sql_def *>(pSql);

	pSqlDef->m_pSql1->append(colDef.m_columnName).append(", ");

	return;
}


oracle_creater::oracle_creater(const std::string &key, const std::string &userName,
		const std::string &password, const std::string &connectString,
		const std::string &charset,
		bool usePool, int maxPoolSize, int minPoolSize, const std::string &ncharset) :
	m_key(key), m_userName(userName), m_password(password), m_connectString(
			connectString), m_charset(charset), m_ncharset(ncharset), m_usePool(usePool), m_maxPoolSize(maxPoolSize),
			m_minPoolSize(minPoolSize)
{
	try
	{
		if (usePool)
		{
			m_pEnv = oracle::occi::Environment::createEnvironment(m_charset, m_ncharset, oracle::occi::Environment::THREADED_MUTEXED);
//			m_pConnectionPool = m_pEnv->createConnectionPool(userName, password,
//					connectString, minPoolSize, maxPoolSize);
			m_pStatelessConnectionPool = m_pEnv->createStatelessConnectionPool(userName,
					password, connectString, minPoolSize, maxPoolSize);
		}
		else
		{
			m_pEnv = oracle::occi::Environment::createEnvironment(m_charset, m_ncharset, oracle::occi::Environment::THREADED_MUTEXED);
			m_pStatelessConnectionPool = NULL;
		}
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_ORACREATER_CONDUCT, "oracle_creater::oracle_creater : %s", e.what());
	}
}

oracle_creater::~oracle_creater()
{
	if (m_usePool)
	{
		m_pEnv->terminateStatelessConnectionPool(m_pStatelessConnectionPool,
				oracle::occi::StatelessConnectionPool::SPD_FORCE);
	}
	oracle::occi::Environment::terminateEnvironment(m_pEnv);

	database_factory::SGetInstance()->Unregister(m_key);
}

void oracle_creater::Reset()
{
	try
	{
		if (m_usePool)
		{
			m_pEnv = oracle::occi::Environment::createEnvironment(m_charset, m_ncharset, oracle::occi::Environment::THREADED_MUTEXED);
			m_pStatelessConnectionPool = m_pEnv->createStatelessConnectionPool(m_userName,
					m_password, m_connectString, m_minPoolSize, m_maxPoolSize);
		}
		else
		{
			m_pEnv = oracle::occi::Environment::createEnvironment();
			m_pStatelessConnectionPool = NULL;
		}
	}
	catch (oracle::occi::SQLException &e)
	{
		std::string message = "oracle_creater::Reset :";
		throw sql_exception(DATABASE_ORACREATER_CONDUCT, "oracle_creater::Reset : %s", e.what());
	}
}

void oracle_creater::Register()
{
	database_factory::SGetInstance()->Register(m_key, this);
}

i_connection *oracle_creater::CreateOrigConnection(unsigned long int threadId) throw (sql_exception)
{
	try
	{
			return new oracle_connection(this, m_pEnv->createConnection(m_userName, m_password, m_connectString), m_key, threadId, m_charset);
	}
	catch (oracle::occi::SQLException &e)
	{
		std::string message = "oracle_creater::CreateConnection :";
		message.append(m_connectString);
		message.append(":");
		message.append(m_userName);
		message.append(":");
		message.append(m_password);
		message.append(":");
		message.append(e.what());
		throw sql_exception(DATABASE_CONNECTION_CREATE, message.c_str());
	}
}

i_connection *oracle_creater::CreateConnection(unsigned long int threadId) throw (sql_exception)
{
	try
	{
		if (m_usePool)
		{
			return new oracle_connection(this, m_pStatelessConnectionPool->getConnection(), m_key, threadId, m_charset);
		}
		else
		{
			return new oracle_connection(this, m_pEnv->createConnection(m_userName, m_password, m_connectString), m_key, threadId, m_charset);
		}
	}
	catch (oracle::occi::SQLException &e)
	{
		std::string message = "oracle_creater::CreateConnection :";
		message.append(m_connectString);
		message.append(":");
		message.append(m_userName);
		message.append(":");
		message.append(m_password);
		message.append(":");
		message.append(e.what());
		throw sql_exception(DATABASE_CONNECTION_CREATE, message.c_str());
	}
}

i_connection *oracle_creater::CreateConnection(const std::string &userName,
		const std::string &password, const std::string &connectString, unsigned long int threadId) throw (sql_exception)
{
	try
	{
		if (m_usePool)
		{
			return new oracle_connection(this, m_pStatelessConnectionPool->getConnection(userName, password, connectString), m_key, threadId, m_charset);
		}
		else
		{
			return new oracle_connection(this, m_pEnv->createConnection(userName, password, connectString), m_key, threadId, m_charset);
		}
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_CONNECTION_CREATE, "oracle_creater::CreateConnection : %s", e.what());
	}
}

void oracle_creater::TerminateConnection(i_connection *pConnection)
{
	try
	{
		oracle_connection *pConn = (oracle_connection *)pConnection;
		if (m_usePool)
		{
			m_pStatelessConnectionPool->releaseConnection(pConn->GetConnection());
		}
		else
		{
			m_pEnv->terminateConnection(pConn->GetConnection());
		}
		pConn->SetClose();
		delete pConn;
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_CONNECTION_DESTROY, "oracle_creater::TerminateConnection : %s", e.what());
	}
}

void oracle_creater::TerminateOrigConnection(i_connection *pConnection)
{
	try
	{
		oracle_connection *pConn = (oracle_connection *)pConnection;
			m_pEnv->terminateConnection(pConn->GetConnection());
		pConn->SetClose();
		delete pConn;
	}
	catch (oracle::occi::SQLException &e)
	{
		throw sql_exception(DATABASE_CONNECTION_DESTROY, "oracle_creater::TerminateConnection : %s", e.what());
	}
}

bool oracle_creater::IsValid(i_connection *pConn)
{
	i_prepared_statement *pStmt = NULL;
	i_result_set *pRs = NULL;
	try
	{
		pStmt = pConn->PrepareStatement("select sysdate from dual");
		pRs = pStmt->ExecuteQuery();

		pRs->Close();
		pStmt->Close();
		delete pRs;
		pStmt->Close();
		delete pStmt;
	}
	catch (sql_exception &e)
	{
		if (pRs != NULL)
		{
			pRs->Close();
			delete pRs;
		}
		if (pStmt != NULL)
		{
			pStmt->Close();
			delete pStmt;
		}
		return false;
	}

	return true;
}

std::string oracle_creater::GetDbname()
{
	return m_key;
}

oracle::occi::Environment *oracle_creater::GetEnvironment()
{
	return m_pEnv;
}

InsertSQL_Fun oracle_creater::GetInsertSQLFunction()
{
	return &OraInsertSQL;
}

UpdateSQL_Fun oracle_creater::GetUpdateSQLFunction()
{
	return &OraUpdateSQL;
}

FindSQL_Fun oracle_creater::GetFindSQLFunction()
{
	return &OraFindSQL;
}

DumySQL_Fun oracle_creater::GetDumySQLFunction()
{
	return &OraDumySQL;
}

FindLobForUpdateSQL_Fun oracle_creater::GetFindLobForUpdateSQLFunction()
{
	return &OraFindLobForUpdateSQL;
}


}
