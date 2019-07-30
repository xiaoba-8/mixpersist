/*
 * oracle_result_set.h
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#ifndef ORARESULTSET_H_
#define ORARESULTSET_H_

#include <occi.h>
#include <mix/database/i_result_set.h>
#include "oracle_statement.h"

namespace mix {

class oracle_result_set: public i_result_set
{
public:
	oracle_result_set(oracle_statement *, oracle::occi::Statement *, oracle::occi::ResultSet *, std::string);
	virtual ~oracle_result_set();

	virtual bool Next();
	virtual void Close();

	virtual Integer GetInt(unsigned int colIndex);
	virtual UInteger GetUInt(unsigned int colIndex);
	virtual UInt64 GetUInt64(unsigned int colIndex);
	virtual Float GetFloat(unsigned int colIndex);
	virtual Double GetDouble(unsigned int colIndex);
	virtual std::string GetString(unsigned int colIndex);
	virtual AnyType GetObject(unsigned int colIndex);

	virtual void SetCharSet(unsigned int colIndex, const std::string & charSet);
	virtual std::string	GetCharSet(unsigned int colIndex) const;

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

	virtual oracle::occi::Bfile GetBFile(unsigned int colIndex);

	virtual int GetColumnCount();
	virtual std::string GetColumnName(unsigned int colIndex);
	virtual unsigned int GetColumnIndex(std::string colName);

	virtual bool IsNull(unsigned int colIndex) const;

	oracle_statement *GetStatement() { return m_pOraStatement; }
private:
	oracle_statement *m_pOraStatement;
	oracle::occi::Statement *m_pStatement;
	oracle::occi::ResultSet *m_pResultSet;
	std::string	m_charset;
};

}

#endif /* ORARESULTSET_H_ */
