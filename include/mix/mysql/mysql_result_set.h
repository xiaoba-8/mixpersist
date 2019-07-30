/*
 * mysql_result_set.h
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#ifndef MYSQLRESULTSET_H_
#define MYSQLRESULTSET_H_

#include <mysql_connection.h>
#include <cppconn/resultset.h>
//#include <mysql-cppconn/mysql/jdbc.h>
#include <mix/database/i_result_set.h>

namespace mix {

class mysql_result_set: public i_result_set
{
public:
	mysql_result_set(sql::ResultSet *);
	virtual ~mysql_result_set();

	virtual bool Next();
	virtual void Close();

	virtual Integer GetInt(unsigned int colIndex);
	virtual UInteger GetUInt(unsigned int colIndex);
	virtual UInt64 GetUInt64(unsigned int colIndex);
	virtual Float GetFloat(unsigned int colIndex);
	virtual Double GetDouble(unsigned int colIndex);
	virtual std::string GetString(unsigned int colIndex);
	virtual AnyType GetObject(unsigned int colIndex);

	virtual Date GetDate(unsigned int colIndex);
	virtual Timestamp GetTimestamp(unsigned int colIndex);
	virtual Blob GetBlob(unsigned int colIndex);
	virtual Clob GetClob(unsigned int colIndex);

	virtual Integer GetInt(std::string colName);
	virtual UInteger GetUInt(std::string colName);
	virtual Float GetFloat(std::string colName);
	virtual Double GetDouble(std::string colName);
	virtual std::string GetString(std::string colName);
	virtual AnyType GetObject(std::string colName);

	virtual Date GetDate(std::string colName);
	virtual Timestamp GetTimestamp(std::string colName);
	virtual Blob GetBlob(std::string colName);
	virtual Clob GetClob(std::string colName);

	virtual int GetColumnCount();
	virtual std::string GetColumnName(unsigned int colIndex);
	virtual unsigned int GetColumnIndex(std::string colName);

	virtual bool IsNull(unsigned int colIndex) const;

private:
	sql::ResultSet *m_pResultSet;
};

}

#endif /* MySqlRESULTSET_H_ */
