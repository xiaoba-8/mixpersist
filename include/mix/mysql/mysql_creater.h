/*
 * mysql_creater.h
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#ifndef MySqlCREATER_H_
#define MySqlCREATER_H_

#include <mysql_connection.h>
//#include <mysql-cppconn/mysql/jdbc.h>
#include <mix/database/i_creater.h>

namespace mix
{

class mysql_creater: public i_creater
{
public:
	mysql_creater(const std::string &key, const std::string &userName = "",
			const std::string &password = "", const std::string &connectString =
					"", bool usePool = false, int maxPoolSize = 20,
			int minPoolSize = 10);
	virtual ~mysql_creater();

	virtual void Reset();
	virtual void Register();
	virtual i_connection *CreateOrigConnection(unsigned long int threadId) throw (sql_exception);
	virtual i_connection *CreateConnection(unsigned long int threadId) throw (sql_exception);
	virtual i_connection *CreateConnection(const std::string &userName,
			const std::string &password, const std::string &connectString, unsigned long int threadId) throw (sql_exception);
	virtual void TerminateConnection(i_connection *);
	virtual void TerminateOrigConnection(i_connection *);

	virtual bool IsValid(i_connection *);
	virtual std::string GetDbname();

	virtual InsertSQL_Fun GetInsertSQLFunction();
	virtual UpdateSQL_Fun GetUpdateSQLFunction();
	virtual FindSQL_Fun GetFindSQLFunction();
	virtual DumySQL_Fun GetDumySQLFunction();
	virtual FindLobForUpdateSQL_Fun GetFindLobForUpdateSQLFunction();
private:

    sql::Driver *m_pDriver;

	std::string m_key;
	std::string m_userName;
	std::string m_password;
	std::string m_connectString;
	bool m_usePool;
	int m_maxPoolSize;
	int m_minPoolSize;
};

}

#endif /* MySqlCREATER_H_ */
