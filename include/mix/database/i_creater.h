/*
 * i_creater.h
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#ifndef ICREATER_H_
#define ICREATER_H_

#include <string>
#include "sql_exception.h"
#include "i_connection.h"
#include "dbdatas.h"

#include "dbmapping.h"

namespace mix
{

class i_creater
{
public:
	virtual ~i_creater() {}

	virtual void Reset() = 0;

	virtual void Register() = 0;

	virtual i_connection *CreateOrigConnection(unsigned long int threadId) throw (sql_exception) = 0;
	virtual i_connection *CreateConnection(unsigned long int threadId) throw (sql_exception) = 0;

	virtual i_connection *CreateConnection(const std::string &userName, const std::string &password, const std::string &connectString, unsigned long int threadId) throw (sql_exception) = 0;

	virtual void TerminateConnection(i_connection *) = 0;
	virtual void TerminateOrigConnection(i_connection *) = 0;

	virtual bool IsValid(i_connection *) = 0;
	virtual std::string GetDbname() = 0;

	virtual InsertSQL_Fun GetInsertSQLFunction() = 0;
	virtual UpdateSQL_Fun GetUpdateSQLFunction() = 0;
	virtual FindSQL_Fun GetFindSQLFunction() = 0;
	virtual DumySQL_Fun GetDumySQLFunction() = 0;
	virtual FindLobForUpdateSQL_Fun GetFindLobForUpdateSQLFunction() = 0;
};
}

#endif /* ICREATER_H_ */
