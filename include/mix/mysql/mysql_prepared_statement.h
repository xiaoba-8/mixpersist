/*
 * mysql_prepared_statement.h
 *
 *  Created on: 2018-2-6
 *      Author: xiaoba-8
 */

#ifndef MYSQLPREPAREDSTATEMENT_H_
#define MYSQLPREPAREDSTATEMENT_H_

#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
//#include <mysql-cppconn/mysql/jdbc.h>
#include <mix/database/i_prepared_statement.h>
#include "mysql_statement.h"

namespace mix
{

class mysql_prepared_statement: public i_prepared_statement, public mysql_statement
{
public:
	mysql_prepared_statement(sql::Connection *, sql::PreparedStatement *);
	virtual ~mysql_prepared_statement();

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

	virtual i_result_set *ExecuteQuery() throw (sql_exception);
	virtual int ExecuteUpdate() throw (sql_exception);

	virtual void SetNull(unsigned int paramIndex, int type);
	virtual void SetInt(unsigned int paramIndex, Integer x);
	virtual void SetUInt(unsigned int paramIndex, UInteger x);
	virtual void SetUInt64(unsigned int paramIndex, UInt64 x);
	virtual void SetFloat(unsigned int paramIndex, Float x);
	virtual void SetDouble(unsigned int paramIndex, Double x);
	virtual void SetString(unsigned int paramIndex, const std::string &x);

	virtual void SetDate(unsigned int paramIndex, const Date &x);
	virtual void SetTimestamp(unsigned int paramIndex, const Timestamp &x);
	virtual void SetBlob(unsigned int paramIndex, Blob &x);
	virtual void SetClob(unsigned int paramIndex, Clob &x);

	virtual bool NeedUpdateBlob();
};
}

#endif /* PREPAREDSTATEMENT_H_ */
