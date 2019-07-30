/*
 * mysql_statement.h
 *
 *  Created on: 2018-2-6
 *      Author: xiaoba-8
 */

#ifndef MYSQLSTATEMENT_H_
#define MYSQLSTATEMENT_H_

#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
//#include <mysql-cppconn/mysql/jdbc.h>
#include <mix/database/i_statement.h>

namespace mix {

class mysql_statement : public i_statement
{
public:
	mysql_statement(sql::Connection *, sql::Statement *);
	virtual ~mysql_statement();

	virtual i_result_set *ExecuteQuery(std::string) throw (sql_exception);
	virtual int ExecuteUpdate(std::string) throw (sql_exception);

	virtual int GetQueryTimeout();
	virtual void SetQueryTimeout(long);
	virtual bool Execute(std::string) throw (sql_exception);
	virtual i_result_set *GetResultSet();
	virtual int GetUpdateCount();
	virtual int GetFetchSize();
	virtual void SetFetchSize(int);

	virtual void SetAutoCommit(bool bAutoCommit=true);
	virtual bool GetAutoCommit();
	virtual void Commit();
	virtual void Rollback();
	virtual void Close();


protected:
	sql::Connection *m_pConn;
	sql::Statement *m_pStatement;
};
}

#endif /* STATEMENT_H_ */
