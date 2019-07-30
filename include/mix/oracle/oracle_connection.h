/*
 * Connection.h
 *
 *  Created on: 2018-2-6
 *      Author: xiaoba-8
 */

#ifndef ORACONNECTION_H_
#define ORACONNECTION_H_

#include <occi.h>
#include <string>
#include <mix/database/i_connection.h>
#include "i_ora_creater.h"

namespace mix {

class oracle_connection : public i_connection
{
public:
	oracle_connection(i_ora_creater *, oracle::occi::Connection *, std::string dbname, unsigned long int threadId, std::string charset);
	virtual ~oracle_connection();

	virtual i_statement *CreateStatement() throw (sql_exception);
	virtual i_prepared_statement *PrepareStatement(std::string sql) throw (sql_exception);
	virtual void SetAutoCommit(bool bAutoCommit=true);
	virtual bool GetAutoCommit();
	virtual void Commit();
	virtual void Rollback();
	virtual void Close();
	virtual bool IsClosed();

	virtual void SetClose();

	virtual std::string GetDbname();
	virtual unsigned long int GetThreadId();
	virtual void SetThreadId(unsigned long int threadId);

	oracle::occi::Connection *GetConnection();

	i_ora_creater *GetCreater();
	void SetStatement(oracle::occi::Statement *pStmt);
private:
	oracle_connection(oracle_connection &);
	oracle::occi::Statement *GetStatement();
	i_ora_creater *m_pCreater;
	oracle::occi::Connection *m_pConn;
	oracle::occi::Statement *m_pStatement;

	std::string m_dbname;
	unsigned long int m_threadId;
	std::string m_charset;
	bool m_bAutoCommit;
	bool m_bClosed;
};

}


#endif /* CONNECTION_H_ */
