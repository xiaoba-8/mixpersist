/*
 * transaction_manager.h
 *
 *  Created on: 2018-4-15
 *      Author: xiaoba-8
 */

#ifndef TRANSACTIONMANAGER_H_
#define TRANSACTIONMANAGER_H_

#include <map>
#include "dbmapping.h"
#include "i_connection.h"

namespace mix
{

class transaction_manager
{
private:
	transaction_manager(unsigned long int id, std::string dbname = "");
public:
	virtual ~transaction_manager();

	/*
	 * Keep connection
	 */
	void Keep();
	/*
	 * Release connection
	 */
	void Release();

	void Begin();
	void Commit();
	void Rollback();

	static transaction_manager *SGetTransactionManager(std::string dbname = "");
	static void STerminateConnection(i_connection *pConn = NULL);

	static void Cleanup(void *pConn);
	static bool TerminateByThreadId(unsigned long int id);

	i_connection *GetConnection();

	bool Equal(i_connection *pConn);
	inline unsigned long int GetId() { return m_id; }

	virtual InsertSQL_Fun GetInsertSQLFunction();
	virtual UpdateSQL_Fun GetUpdateSQLFunction();
	virtual FindSQL_Fun GetFindSQLFunction();
	virtual DumySQL_Fun GetDumySQLFunction();
	virtual FindLobForUpdateSQL_Fun GetFindLobForUpdateSQLFunction();

private:
	static std::string GetKey(unsigned long int id, std::string dbname);

	bool Terminate();
	bool IsTermiated();

	static std::map<std::string, transaction_manager *> m_managerMap;
	unsigned int m_transCount;
	unsigned int m_keepCount;
	i_connection *m_pConn;
	unsigned long int m_id;
	bool m_isTerminate;
	std::string m_dbname;

};

}

#endif /* TRANSACTIONMANAGER_H_ */
