/*
 * oracle_result_set.cpp
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#include <stdlib.h>
#include <sstream>
#include <mix/database/db_errno.h>
#include <mix/database/sql_exception.h>
#include <mix/oracle/oracle_result_set.h>

namespace mix
{

oracle_result_set::oracle_result_set(oracle_statement *pOraStatement,
		oracle::occi::Statement *pStatement,
		oracle::occi::ResultSet *pResultSet, std::string charset) :
		m_pOraStatement(pOraStatement), m_pStatement(pStatement),
		m_pResultSet(pResultSet), m_charset(charset)
{

}

oracle_result_set::~oracle_result_set()
{

}

bool oracle_result_set::Next()
{
	if (this->m_pOraStatement->GetConnection()->IsClosed())
		throw sql_exception(DATABASE_CLOSED, "oracle_result_set: Connection Closed!");

	int next = m_pResultSet->next();
	if (next == oracle::occi::ResultSet::END_OF_FETCH)
		return false;
	else
		return true;
}

void oracle_result_set::Close()
{
	if (this->m_pOraStatement->GetConnection()->IsClosed())
		throw sql_exception(DATABASE_CLOSED, "oracle_result_set: Connection Closed!");

	m_pStatement->closeResultSet(m_pResultSet);
}

Integer oracle_result_set::GetInt(unsigned int colIndex)
{
	return Integer(m_pResultSet->getInt(colIndex), m_pResultSet->isNull(colIndex));
}

UInteger oracle_result_set::GetUInt(unsigned int colIndex)
{
	return UInteger(m_pResultSet->getUInt(colIndex), m_pResultSet->isNull(colIndex));
}

UInt64 oracle_result_set::GetUInt64(unsigned int colIndex)
{
	oracle::occi::Number x = m_pResultSet->getNumber(colIndex);
	std::string value = x.toText(this->m_pOraStatement->GetConnection()->GetCreater()->GetEnvironment(), "99999999999999999999");
	return UInt64(atoll(value.c_str()), x.isNull());
}

Float oracle_result_set::GetFloat(unsigned int colIndex)
{
	return Float(m_pResultSet->getFloat(colIndex), m_pResultSet->isNull(colIndex));
}

Double oracle_result_set::GetDouble(unsigned int colIndex)
{
	return Double(m_pResultSet->getDouble(colIndex), m_pResultSet->isNull(colIndex));
}

std::string oracle_result_set::GetString(unsigned int colIndex)
{
	return m_pResultSet->getString(colIndex);
}

void oracle_result_set::SetCharSet(unsigned int colIndex,
		const std::string & charSet)
{
	return m_pResultSet->setCharSet(colIndex, charSet);
}

std::string oracle_result_set::GetCharSet(unsigned int colIndex) const
{
	return m_pResultSet->getCharSet(colIndex);
}

Date oracle_result_set::GetDate(unsigned int colIndex)
{
	int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;

	oracle::occi::Date oDate = m_pResultSet->getDate(colIndex);
	Date dt;

	if (oDate.isNull())
	{
		oDate.getDate(year, month, day, hour, minute, second);
		dt.SetLocalDate(year, month, day, hour, minute, second);
	}
	else
	{
		dt.SetNull();
	}
	return dt;
}

Timestamp oracle_result_set::GetTimestamp(unsigned int colIndex)
{
	int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	unsigned int fs = 0;

	oracle::occi::Timestamp oTimestamp = m_pResultSet->getTimestamp(colIndex);

	Timestamp ts;
	if (oTimestamp.isNull())
	{
		ts.SetNull();

		return ts;
	}
	else
	{
		oTimestamp.getDate(year, month, day);
		oTimestamp.getTime(hour, minute, second, fs);

		ts.SetLocalDate(year, month, day);
		ts.SetLocalTime(hour, minute, second, fs);

		return ts;
	}
	return ts;
}

Blob oracle_result_set::GetBlob(unsigned int colIndex)
{
	oracle::occi::Blob blob = m_pResultSet->getBlob(colIndex);

	char buffer[1024];
	std::string ss;
	int n = 0;

	memset(buffer, 0, 1024);

	Blob lob;

	if (blob.isNull())
	{
	}
	else
	{
		oracle::occi::Stream *pStream = blob.getStream();

		while ((n = pStream->readBuffer(buffer, 1024)) > 0)
		{
			ss.append(buffer, n);
			//ss << std::string(buffer, n);
		}
		blob.closeStream(pStream);

		lob.SetString(ss);
	}
	lob.SetNeedUpdate(false);
	return lob;
}

Clob oracle_result_set::GetClob(unsigned int colIndex)
{
	oracle::occi::Clob clob = m_pResultSet->getClob(colIndex);

	char buffer[1024];
	std::string ss;
	int n = 0;

	memset(buffer, 0, 1024);

	Clob lob;

	if (clob.isNull())
	{
	}
	else
	{
		oracle::occi::Stream *pStream = clob.getStream();

		while ((n = pStream->readBuffer(buffer, 1024)) > 0)
		{
			ss.append(buffer, n);
		}
		clob.closeStream(pStream);
		//clob.close();
		lob.SetString(ss);
	}
	lob.SetNeedUpdate(false);
	return lob;
}

oracle::occi::Bfile oracle_result_set::GetBFile(unsigned int colIndex)
{
	return m_pResultSet->getBfile(colIndex);
}

AnyType oracle_result_set::GetObject(unsigned int colIndex)
{
	if (m_pResultSet->isNull(colIndex))
		return AnyType();
	else
	{
		std::vector<oracle::occi::MetaData> attributeList =
				m_pResultSet->getColumnListMetaData();
		oracle::occi::MetaData metaData = attributeList[colIndex-1];
		switch (metaData.getInt(oracle::occi::MetaData::ATTR_DATA_TYPE))
		{
		case SQLT_CHR: /* (ORANET TYPE) character string */
			return AnyType(m_pResultSet->getString(colIndex));
		case SQLT_NUM: /* (ORANET TYPE) oracle numeric */
			return AnyType(m_pResultSet->getDouble(colIndex));
		case SQLT_INT: /* (ORANET TYPE) integer */
			return AnyType(m_pResultSet->getInt(colIndex));
		case SQLT_FLT: /* (ORANET TYPE) Floating point number */
			return AnyType(m_pResultSet->getFloat(colIndex));
		case SQLT_STR: /* zero terminated string */
			return AnyType(m_pResultSet->getString(colIndex));
		case SQLT_VNU: /* NUM with preceding length byte */
			return AnyType();
		case SQLT_PDN: /* (ORANET TYPE) Packed Decimal Numeric */
			return AnyType(m_pResultSet->getDouble(colIndex));
		case SQLT_LNG: /* long */
			return AnyType(m_pResultSet->getInt(colIndex));
		case SQLT_VCS: /* Variable character string */
			return AnyType(m_pResultSet->getString(colIndex));
		case SQLT_NON: /* Null/empty PCC Descriptor entry */
			return AnyType();
		case SQLT_RID: /* rowid */
			return AnyType(m_pResultSet->getInt(colIndex));
		case SQLT_DAT: /* date in oracle format */
		{
			return AnyType(GetDate(colIndex));
		}
		case SQLT_VBI: /* binary in VCS format */
			return AnyType();
		case SQLT_BFLOAT: /* Native Binary float*/
			return AnyType(m_pResultSet->getFloat(colIndex));
		case SQLT_BDOUBLE: /* NAtive binary double */
			return AnyType(m_pResultSet->getDouble(colIndex));
		case SQLT_BIN: /* binary data(DTYBIN) */
			return AnyType();
		case SQLT_LBI: /* long binary */
			return AnyType();
		case SQLT_UIN: /* unsigned integer */
			return AnyType(m_pResultSet->getUInt(colIndex));
		case SQLT_SLS: /* Display sign leading separate */
			return AnyType();
		case SQLT_LVC: /* Longer longs (char) */
		case SQLT_LVB: /* Longer long binary */
		case SQLT_AFC: /* Ansi fixed char */
			return AnyType(m_pResultSet->getString(colIndex));
		case SQLT_AVC: /* Ansi Var char */
			return AnyType(m_pResultSet->getString(colIndex));
		case SQLT_IBFLOAT: /* binary float canonical */
			return AnyType(m_pResultSet->getFloat(colIndex));
		case SQLT_IBDOUBLE: /* binary double canonical */
			return AnyType(m_pResultSet->getDouble(colIndex));
		case SQLT_CUR: /* cursor  type */
			return AnyType();
		case SQLT_RDD: /* rowid descriptor */
			return AnyType();
		case SQLT_LAB: /* label type */
			return AnyType();
		case SQLT_OSL: /* oslabel type */
			return AnyType();

		case SQLT_NTY: /* named object type */
			return AnyType();
		case SQLT_REF: /* ref type */
			return AnyType();
		case SQLT_CLOB: /* character lob */
			return AnyType(GetClob(colIndex));
		case SQLT_BLOB: /* binary lob */
			return AnyType(GetBlob(colIndex));
		case SQLT_BFILEE: /* binary file lob */
			return AnyType();
		case SQLT_CFILEE: /* character file lob */
			return AnyType();
		case SQLT_RSET: /* result set type */
			return AnyType();
		case SQLT_NCO: /* named collection type (varray or nested table) */
			return AnyType();
		case SQLT_VST: /* OCIString type */
			return AnyType();
		case SQLT_ODT: /* OCIDate type */
			return AnyType();

			/* datetimes and intervals */
		case SQLT_DATE: /* ANSI Date */
		{
			return AnyType(GetDate(colIndex));
		}
		case SQLT_TIME: /* TIME */
			return AnyType();
		case SQLT_TIME_TZ: /* TIME WITH TIME ZONE */
			return AnyType();
		case SQLT_TIMESTAMP: /* TIMESTAMP */
		{
			return AnyType(GetTimestamp(colIndex));
		}
		case SQLT_TIMESTAMP_TZ: /* TIMESTAMP WITH TIME ZONE */
		{
			return AnyType(GetTimestamp(colIndex));
		}
		case SQLT_INTERVAL_YM: /* INTERVAL YEAR TO MONTH */
			return AnyType();
		case SQLT_INTERVAL_DS: /* INTERVAL DAY TO SECOND */
			return AnyType();
		case SQLT_TIMESTAMP_LTZ: /* TIMESTAMP WITH LOCAL TZ */
			return AnyType();

		case SQLT_PNTY: /* pl/sql representation of named types */
		default:
			return AnyType();
		}
	}
}

Integer oracle_result_set::GetInt(std::string colName)
{
	return GetInt(GetColumnIndex(colName));
}

UInteger oracle_result_set::GetUInt(std::string colName)
{
	return GetUInt(GetColumnIndex(colName));
}

Float oracle_result_set::GetFloat(std::string colName)
{
	return GetFloat(GetColumnIndex(colName));
}

Double oracle_result_set::GetDouble(std::string colName)
{
	return GetDouble(GetColumnIndex(colName));
}

std::string oracle_result_set::GetString(std::string colName)
{
	return GetString(GetColumnIndex(colName));
}

AnyType oracle_result_set::GetObject(std::string colName)
{
	return GetObject(GetColumnIndex(colName));
}

Date oracle_result_set::GetDate(std::string colName)
{
	return GetDate(GetColumnIndex(colName));
}

Timestamp oracle_result_set::GetTimestamp(std::string colName)
{
	return GetTimestamp(GetColumnIndex(colName));
}

Blob oracle_result_set::GetBlob(std::string colName)
{
	return GetBlob(GetColumnIndex(colName));
}

Clob oracle_result_set::GetClob(std::string colName)
{
	return GetClob(GetColumnIndex(colName));
}

int oracle_result_set::GetColumnCount()
{
	std::vector<oracle::occi::MetaData> attributeList =
			m_pResultSet->getColumnListMetaData();

	return attributeList.size();
}

std::string oracle_result_set::GetColumnName(unsigned int colIndex)
{
	std::vector<oracle::occi::MetaData> attributeList =
			m_pResultSet->getColumnListMetaData();

	return attributeList[colIndex].getString(oracle::occi::MetaData::ATTR_NAME);
}

unsigned int oracle_result_set::GetColumnIndex(std::string colName)
{
	std::vector<oracle::occi::MetaData> attributeList =
			m_pResultSet->getColumnListMetaData();

	for (unsigned int i = 0; i < attributeList.size(); i++)
	{
		if (attributeList[i].getString(oracle::occi::MetaData::ATTR_NAME) == colName)
			return i;
	}
	throw sql_exception(DATABASE_RESULTSET_WRONGCOL, "Wrong column name:%s", colName.c_str());
}

bool oracle_result_set::IsNull(unsigned int colIndex) const
{
	return m_pResultSet->isNull(colIndex);
}

}
