/*
 * mysql_connection.h
 *
 *  Created on: 2018-2-6
 *      Author: xiaoba-8
 */

#ifndef MYSQLCONNECTION_H_
#define MYSQLCONNECTION_H_


#include <mysql_connection.h>
#include <cppconn/exception.h>
//#include <mysql-cppconn/mysql/jdbc.h>
#include <mix/database/i_connection.h>
#include <mix/database/i_creater.h>

namespace mix {

class mysql_connection : public i_connection
{
public:
	mysql_connection(i_creater *, sql::Connection *, std::string dbname, unsigned long int threadId);
	virtual ~mysql_connection();

	virtual i_statement *CreateStatement() throw (sql_exception);
	virtual i_prepared_statement *PrepareStatement(std::string sql) throw (sql_exception);
	virtual void SetAutoCommit(bool bAutoCommit=true);
	virtual bool GetAutoCommit();
	virtual void Commit();
	virtual void Rollback();
	virtual void Close();
	virtual bool IsClosed();

	void SetClose();

	virtual std::string GetDbname();
	virtual unsigned long int GetThreadId();
	virtual void SetThreadId(unsigned long int threadId);

	sql::Connection *GetConnection();
private:
	i_creater *m_pCreater;
	sql::Connection *m_pConn;
	std::string m_dbname;
	unsigned long int m_threadId;
	bool m_bClosed;
};

}

#endif /* CONNECTION_H_ */
