/*
 * mysql_creater.cpp
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */


#include <mix/database/db_errno.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
//#include <mysql-cppconn/mysql/jdbc.h>
#include <mix/database/database_factory.h>
#include <mix/mysql/mysql_connection.h>
#include <mix/mysql/mysql_creater.h>

#define MYSQL_DRIVER

namespace mix
{

void MysqlInsertSQL(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql)
{
	if (colDef.m_autoincr) return;

	sql_def *pSqlDef = static_cast<sql_def *>(pSql);

	pSqlDef->m_pSql1->append(colDef.m_columnName).append(", ");
	pSqlDef->m_pSql2->append("?, ");

	return;
}

void MysqlUpdateSQL(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql)
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

void MysqlFindSQL(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql)
{
	sql_def *pSqlDef = static_cast<sql_def *>(pSql);

	pSqlDef->m_pSql1->append(colDef.m_columnName).append(", ");

	if (colDef.m_identify)
	{
		pSqlDef->m_pSql2->append(colDef.m_columnName).append("=? and ");
	}

	return;
}

void MysqlFindLobForUpdateSQL(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql)
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

void MysqlDumySQL(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql)
{
	sql_def *pSqlDef = static_cast<sql_def *>(pSql);

	pSqlDef->m_pSql1->append(colDef.m_columnName).append(", ");

	return;
}

mysql_creater::mysql_creater(const std::string &key, const std::string &userName,
		const std::string &password, const std::string &connectString,
		bool usePool, int maxPoolSize, int minPoolSize) :
	m_key(key), m_userName(userName), m_password(password), m_connectString(
			connectString), m_usePool(usePool), m_maxPoolSize(maxPoolSize),
			m_minPoolSize(minPoolSize)
{
#ifdef  MYSQL_DRIVER
	m_pDriver = get_driver_instance();
#endif
}

mysql_creater::~mysql_creater()
{
}

void mysql_creater::Reset()
{
#ifdef  MYSQL_DRIVER
	m_pDriver = get_driver_instance();
#endif
}
void mysql_creater::Register()
{
	database_factory::SGetInstance()->Register(m_key, this);
}

i_connection *mysql_creater::CreateConnection(unsigned long int threadId) throw (sql_exception)
{
	try
	{
		return new mysql_connection(this, m_pDriver->connect(m_connectString, m_userName, m_password), m_key, threadId);
	}
	catch (sql::SQLException &e)
	{
		std::string message = "mysql_creater::CreateConnection :";
		message.append(e.what());
		throw sql_exception(DATABASE_CONNECTION_CREATE, message.c_str());
	}
}

i_connection *mysql_creater::CreateOrigConnection(unsigned long int threadId) throw (sql_exception)
{
	try
	{
		return new mysql_connection(this, m_pDriver->connect(m_connectString, m_userName, m_password), m_key, threadId);
	}
	catch (sql::SQLException &e)
	{
		std::string message = "mysql_creater::CreateConnection :";
		message.append(e.what());
		throw sql_exception(DATABASE_CONNECTION_CREATE, message.c_str());
	}
}

i_connection *mysql_creater::CreateConnection(const std::string &userName,
		const std::string &password, const std::string &connectString, unsigned long int threadId) throw (sql_exception)
{
	try
	{
		return new mysql_connection(this, m_pDriver->connect(connectString, userName, password), m_key, threadId);
	}
	catch (sql::SQLException &e)
	{
		std::string message = "mysql_creater::CreateConnection :";
		message.append(e.what());
		throw sql_exception(DATABASE_CONNECTION_CREATE, message.c_str());
	}
}

void mysql_creater::TerminateConnection(i_connection *pConnection)
{
	mysql_connection *pConn = (mysql_connection *)pConnection;
	pConn->GetConnection()->close();
	pConn->SetClose();
	delete pConn;
}

void mysql_creater::TerminateOrigConnection(i_connection *pConnection)
{
	mysql_connection *pConn = (mysql_connection *)pConnection;
	pConn->GetConnection()->close();
	pConn->SetClose();
	delete pConn;
}

bool mysql_creater::IsValid(i_connection *)
{
	return true;
}

std::string mysql_creater::GetDbname()
{
	return m_key;
}


InsertSQL_Fun mysql_creater::GetInsertSQLFunction()
{
	return &MysqlInsertSQL;
}

UpdateSQL_Fun mysql_creater::GetUpdateSQLFunction()
{
	return &MysqlUpdateSQL;
}

FindSQL_Fun mysql_creater::GetFindSQLFunction()
{
	return &MysqlFindSQL;
}

DumySQL_Fun mysql_creater::GetDumySQLFunction()
{
	return &MysqlDumySQL;
}

FindLobForUpdateSQL_Fun mysql_creater::GetFindLobForUpdateSQLFunction()
{
	return &MysqlFindLobForUpdateSQL;
}

}
