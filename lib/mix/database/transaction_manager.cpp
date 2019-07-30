/*
 * transaction_manager.cpp
 *
 *  Created on: 2018-4-15
 *      Author: xiaoba-8
 */

#include <stdio.h>
#include <sstream>
#include "../../../include/mix/database/transaction_manager.h"
#ifdef _WIN32
#	include <Windows.h>
#	include <WinBase.h>
#else
#endif
#include <mix/database/sql_exception.h>
#include <mix/database/database_factory.h>
#include <mix/database/db_errno.h>

#include "db_mutex.h"

namespace mix
{

std::map<std::string, transaction_manager *> transaction_manager::m_managerMap;
static db_mutex s_mutex;

transaction_manager::transaction_manager(unsigned long int id, std::string dbname) :
	m_transCount(0), m_keepCount(0), m_pConn(NULL), m_id(id),
			m_isTerminate(false), m_dbname(dbname)
{

}

transaction_manager::~transaction_manager()
{
}

i_connection *transaction_manager::GetConnection()
{
	if (m_pConn == NULL)
	{
		i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
		if (pCreater != NULL)
		{
			try
			{
				m_pConn = pCreater->CreateConnection(m_id);
			}
			catch (sql_exception &e)
			{
				throw e;
			}
		}
		else
			throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
	}
	m_isTerminate = false;
	return m_pConn;
}

void transaction_manager::Keep()
{
	if (m_transCount == 0)
	{
		m_keepCount++;
	}
}

void transaction_manager::Release()
{
	if (m_transCount == 0)
		m_keepCount--;
	if (m_keepCount < 0)
	{
		m_keepCount = 0;
	}
}

void transaction_manager::Begin()
{
	if (m_transCount == 0)
	{
		try
		{
			GetConnection()->SetAutoCommit(false);
		}
		catch (sql_exception &e)
		{
			std::string message = "transaction_manager::Begin :";
			message.append(e.what());
			throw sql_exception(e.GetErrNo(), message.c_str());
		}
	}
	m_transCount++;
}

void transaction_manager::Commit()
{
	if (m_transCount > 0)
	{
		if (m_transCount == 1)
		{
			GetConnection()->Commit();
		}
		m_transCount--;
	}
	else
	{
		m_transCount = 0;
	}
}

void transaction_manager::Rollback()
{
	if (m_transCount > 0)
	{
		if (m_transCount == 1)
		{
			GetConnection()->Rollback();
		}
		m_transCount--;
	}
	else
	{
		m_transCount = 0;
	}
}

bool transaction_manager::Equal(i_connection *pConn)
{
	return m_pConn == pConn;
}

void transaction_manager::STerminateConnection(i_connection *pConn)
{
	unsigned long int id;
	std::string key;

	if (pConn == NULL)
	{
#ifdef _WIN32
		id = GetCurrentThreadId();
#else
		id = pthread_self();//CommonThread::GetCurrentThreadId();
#endif
		i_creater *pCreater = database_factory::SGetInstance()->GetDefaultCreater();
		if (pCreater == NULL) return;

		key = GetKey(id, pCreater->GetDbname());
	}
	else
	{
		id = pConn->GetThreadId();
		key = GetKey(id, pConn->GetDbname());
	}

	s_mutex.lock();
	transaction_manager *pManager = NULL;

	if (m_managerMap.find(key) != m_managerMap.end())
		pManager = m_managerMap[key];

	if (pManager != NULL && (pConn == NULL || pManager->Equal(pConn)))
	{
		if (pManager->Terminate())
		{
			m_managerMap.erase(key);
			delete pManager;
		}
	}
	else if (pConn != NULL)
	{
		database_factory::SGetInstance()->GetCreater(pConn->GetDbname())->TerminateConnection(
				pConn);
	}
	s_mutex.unlock();
}

void transaction_manager::Cleanup(void *pConnection)
{
	printf("----------------cleanup connection\n");
}

bool transaction_manager::TerminateByThreadId(unsigned long int id)
{
	bool bRet = false;
	std::map<std::string, transaction_manager*>::iterator itr = m_managerMap.begin();

	for (; itr != m_managerMap.end(); ++itr)
	{
		transaction_manager *pManager = (*itr).second;

		if (pManager != NULL && pManager->GetId() == id)
		{
			if (pManager->GetConnection() != NULL)
			{
				pManager->GetConnection()->SetClose();
				bRet = true;
			}
		}
	}

	return bRet;
}

bool transaction_manager::Terminate()
{
	if (m_transCount == 0 && m_keepCount == 0)
	{
		if (m_pConn != NULL)
		{
			database_factory::SGetInstance()->GetCreater(m_pConn->GetDbname())->TerminateConnection(
					m_pConn);
			m_pConn = NULL;
		}
		m_isTerminate = true;
		return true;
	}
	return false;
}

bool transaction_manager::IsTermiated()
{
	return m_isTerminate;
}

transaction_manager *transaction_manager::SGetTransactionManager(std::string dbname)
{
	if (database_factory::SGetInstance()->GetDefaultCreater() == NULL)
	{
		throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
	}
	if (dbname == "")
	{
		dbname = database_factory::SGetInstance()->GetDefaultCreater()->GetDbname();
	}

#ifdef _WIN32
	unsigned long int id = GetCurrentThreadId();
#else
	unsigned long int id = pthread_self();
#endif
	std::string key = GetKey(id, dbname);

	transaction_manager *pManager = NULL;

	s_mutex.lock();
	if (m_managerMap.find(key) == m_managerMap.end())
	{
		pManager = new transaction_manager(id, dbname);
		m_managerMap[key] = pManager;
	}
	else
	{
		pManager = m_managerMap[key];
	}
	s_mutex.unlock();
	return pManager;
}

std::string transaction_manager::GetKey(unsigned long int id, std::string name)
{
	std::stringstream ss;
	ss << id << ":" << name;
	return ss.str();
}

InsertSQL_Fun transaction_manager::GetInsertSQLFunction()
{
	i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
	if (pCreater != NULL)
	{
		return pCreater->GetInsertSQLFunction();
	}
	else
	{
		throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
	}
}

UpdateSQL_Fun transaction_manager::GetUpdateSQLFunction()
{
	i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
	if (pCreater != NULL)
	{
		return pCreater->GetUpdateSQLFunction();
	}
	else
	{
		throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
	}
}

FindSQL_Fun transaction_manager::GetFindSQLFunction()
{
	i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
	if (pCreater != NULL)
	{
		return pCreater->GetFindSQLFunction();
	}
	else
	{
		throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
	}
}

DumySQL_Fun transaction_manager::GetDumySQLFunction()
{
	i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
	if (pCreater != NULL)
	{
		return pCreater->GetDumySQLFunction();
	}
	else
	{
		throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
	}
}

FindLobForUpdateSQL_Fun transaction_manager::GetFindLobForUpdateSQLFunction()
{
	i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
	if (pCreater != NULL)
	{
		return pCreater->GetFindLobForUpdateSQLFunction();
	}
	else
	{
		throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
	}
}

}
