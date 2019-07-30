/*
 * i_connection.h
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#ifndef ICONNECTION_H_
#define ICONNECTION_H_

#include "sql_exception.h"

namespace mix
{

class i_statement;
class i_prepared_statement;

class i_connection {
public:
	virtual ~i_connection() {}
	virtual i_statement *CreateStatement() throw (sql_exception) = 0;
	virtual i_prepared_statement *PrepareStatement(std::string sql) throw (sql_exception) = 0;
	virtual void SetAutoCommit(bool bAutoCommit=true) = 0;
	virtual bool GetAutoCommit() = 0;
	virtual void Commit() = 0;
	virtual void Rollback() = 0;
	virtual void Close() = 0;

	virtual std::string GetDbname() = 0;

	virtual unsigned long int GetThreadId() = 0;
	virtual void SetThreadId(unsigned long int threadId) = 0;
	virtual bool IsClosed() = 0;

	virtual void SetClose() = 0;
};
}

#endif /* ICONNECTION_H_ */
