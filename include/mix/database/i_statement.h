/*
 * i_statement.h
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#ifndef ISTATEMENT_H_
#define ISTATEMENT_H_

#include <iostream>
#include "dbdatas.h"

#include <string>
#include "sql_exception.h"
#include "i_result_set.h"

namespace mix
{

class i_result_set;

class i_statement
{
public:
	virtual ~i_statement() {}

	virtual void Close() = 0;

	virtual i_result_set *ExecuteQuery(std::string sql) throw (sql_exception) = 0;
	virtual int ExecuteUpdate(std::string sql) throw (sql_exception) = 0;

	virtual int GetQueryTimeout() = 0;
	virtual void SetQueryTimeout(long) = 0;

	virtual bool Execute(std::string sql) throw (sql_exception) = 0;

	virtual int GetUpdateCount() = 0;
	virtual int GetFetchSize() = 0;
	virtual void SetFetchSize(int) = 0;
};


}

#endif /* ISTATEMENT_H_ */
