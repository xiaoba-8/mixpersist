/*
 * oracle_statement.h
 *
 *  Created on: 2018-2-6
 *      Author: xiaoba-8
 */

#ifndef ORASTATEMENT_H_
#define ORASTATEMENT_H_

#include <occi.h>
#include <map>

#include "oracle_connection.h"
#include <mix/database/i_prepared_statement.h>

namespace mix {

class oracle_connection;

class oracle_statement : public i_prepared_statement
{
public:
	oracle_statement(oracle_connection *, oracle::occi::Statement *, std::string charset);
	virtual ~oracle_statement();

	virtual i_result_set *ExecuteQuery(std::string) throw (sql_exception);
	virtual int ExecuteUpdate(std::string) throw (sql_exception);

	virtual i_result_set *ExecuteQuery() throw (sql_exception);
	virtual int ExecuteUpdate() throw (sql_exception);

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

	virtual void SetNull(unsigned int paramIndex, int type);
	virtual void SetInt(unsigned int paramIndex, Integer x);
	virtual void SetUInt(unsigned int paramIndex, UInteger x);
	virtual void SetUInt64(unsigned int paramIndex, UInt64 x);
	virtual void SetFloat(unsigned int paramIndex, Float x);
	virtual void SetDouble(unsigned int paramIndex, Double x);
	virtual void SetString(unsigned int paramIndex,	const std::string &x);

	virtual void SetCharSet(unsigned int paramIndex, const std::string & charSet);
	virtual std::string	GetCharSet(unsigned int paramIndex) const;

	virtual int GetInt(unsigned int paramIndex);
	virtual unsigned int GetUInt(unsigned int paramIndex);
	virtual float GetFloat(unsigned int paramIndex);
	virtual double GetDouble(unsigned int paramIndex);
	virtual std::string GetString(unsigned int paramIndex);


	virtual void SetDate(unsigned int paramIndex, const Date &x);
	virtual void SetTimestamp(unsigned int paramIndex, const Timestamp &x);
	virtual void SetBlob(unsigned int paramIndex, Blob &x);
	virtual void SetClob(unsigned int paramIndex, Clob &x);

	virtual Date GetDate(unsigned int paramIndex);
	virtual Timestamp GetTimestamp(unsigned int paramIndex);

	virtual void SetSQL(const std::string &sql);

	virtual bool NeedUpdateBlob();

	oracle_connection *GetConnection() { return m_pConn; }
protected:

	void ClearMap();

	enum LobType {BLOB, CLOB};

	std::map<unsigned int, Lob *>	m_lobValMap;
	std::map<unsigned int, enum LobType>		m_lobTypeMap;

	oracle_connection *m_pConn;
	oracle::occi::Statement *m_pStatement;
	bool	m_closed;
	std::string m_charset;
};
}

#endif /* STATEMENT_H_ */
