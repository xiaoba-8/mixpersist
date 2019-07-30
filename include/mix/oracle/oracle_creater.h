/*
 * oracle_creater.h
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#ifndef ORACREATER_H_
#define ORACREATER_H_

#include <occi.h>
#include <mix/oracle/i_ora_creater.h>

namespace mix
{

class oracle_creater: public i_ora_creater
{
public:
	oracle_creater(const std::string &key, const std::string &userName = "",
			const std::string &password = "", const std::string &connectString =
					"", const std::string &charset = "AL32UTF8", bool usePool = false, int maxPoolSize = 20,
			int minPoolSize = 10, const std::string &ncharset = "AL16UTF16");
	virtual ~oracle_creater();

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
	virtual oracle::occi::Environment *GetEnvironment();

	virtual InsertSQL_Fun GetInsertSQLFunction();
	virtual UpdateSQL_Fun GetUpdateSQLFunction();
	virtual FindSQL_Fun GetFindSQLFunction();
	virtual DumySQL_Fun GetDumySQLFunction();
	virtual FindLobForUpdateSQL_Fun GetFindLobForUpdateSQLFunction();

private:
	//DefaultConnectionPool *m_pDefaultConnectionPool;

	//oracle::occi::ConnectionPool *m_pConnectionPool;
	oracle::occi::StatelessConnectionPool *m_pStatelessConnectionPool;
	oracle::occi::Environment *m_pEnv;

	std::string m_key;
	std::string m_userName;
	std::string m_password;
	std::string m_connectString;
	std::string m_charset;
	std::string m_ncharset;
	bool m_usePool;
	int m_maxPoolSize;
	int m_minPoolSize;
};

}
#endif /* ORACREATER_H_ */
