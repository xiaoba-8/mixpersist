/*
 * mysql_result_set.cpp
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#include <mix/database/db_errno.h>

#include <mix/mysql/mysql_result_set.h>
#include <mix/database/sql_exception.h>

namespace mix
{

mysql_result_set::mysql_result_set(sql::ResultSet *pResultSet) :
	m_pResultSet(pResultSet)
{

}

mysql_result_set::~mysql_result_set()
{

}

bool mysql_result_set::Next()
{
	return m_pResultSet->next();
}

void mysql_result_set::Close()
{
	m_pResultSet->close();
}

Integer mysql_result_set::GetInt(unsigned int colIndex)
{
	return Integer(m_pResultSet->getInt(colIndex),
			m_pResultSet->isNull(colIndex));
}

UInteger mysql_result_set::GetUInt(unsigned int colIndex)
{
	return UInteger(m_pResultSet->getUInt(colIndex),
			m_pResultSet->isNull(colIndex));
}

UInt64 mysql_result_set::GetUInt64(unsigned int colIndex)
{
	return UInt64(m_pResultSet->getUInt64(colIndex),
			m_pResultSet->isNull(colIndex));
}

Float mysql_result_set::GetFloat(unsigned int colIndex)
{
	return Float(m_pResultSet->getDouble(colIndex),
			m_pResultSet->isNull(colIndex));
}

Double mysql_result_set::GetDouble(unsigned int colIndex)
{
	return Double(m_pResultSet->getDouble(colIndex),
			m_pResultSet->isNull(colIndex));
}

std::string mysql_result_set::GetString(unsigned int colIndex)
{
	return m_pResultSet->getString(colIndex);
}

Date mysql_result_set::GetDate(unsigned int colIndex)
{
	Date ts;
	std::string date = m_pResultSet->getString(colIndex);
	ts.FromText(date, "%Y-%m-%d");
	return ts;
}

Timestamp mysql_result_set::GetTimestamp(unsigned int colIndex)
{
	Timestamp ts;
	std::string timestamp = m_pResultSet->getString(colIndex);
	ts.FromText(timestamp, "%Y-%m-%d %H:%M:%S");
	return ts;
}

Blob mysql_result_set::GetBlob(unsigned int colIndex)
{
	Blob lob(m_pResultSet->getBlob(colIndex));
	lob.SetNeedUpdate(false);
	return lob;
}

Clob mysql_result_set::GetClob(unsigned int colIndex)
{
	Clob lob(m_pResultSet->getBlob(colIndex));
	lob.SetNeedUpdate(false);
	return lob;
}

AnyType mysql_result_set::GetObject(unsigned int colIndex)
{
	if (m_pResultSet->isNull(colIndex))
		return AnyType();
	else
	{
		sql::ResultSetMetaData *pMetaData = m_pResultSet->getMetaData();
		int dataType = pMetaData->getColumnType(colIndex);

		switch (dataType)
		{
		case sql::DataType::UNKNOWN:
			return AnyType(m_pResultSet->getString(colIndex));
		case sql::DataType::BIT:
			return AnyType(m_pResultSet->getInt(colIndex));
		case sql::DataType::TINYINT:
			return AnyType(m_pResultSet->getInt(colIndex));
		case sql::DataType::SMALLINT:
			return AnyType(m_pResultSet->getInt(colIndex));
		case sql::DataType::MEDIUMINT:
			return AnyType(m_pResultSet->getInt(colIndex));
		case sql::DataType::INTEGER:
			return AnyType(m_pResultSet->getInt(colIndex));
		case sql::DataType::BIGINT:
			return AnyType(m_pResultSet->getInt(colIndex));
		case sql::DataType::REAL:
			return AnyType(m_pResultSet->getDouble(colIndex));
		case sql::DataType::DOUBLE:
			return AnyType(m_pResultSet->getDouble(colIndex));
		case sql::DataType::DECIMAL:
			return AnyType(m_pResultSet->getDouble(colIndex));
		case sql::DataType::NUMERIC:
			return AnyType(m_pResultSet->getDouble(colIndex));
		case sql::DataType::CHAR:
			return AnyType(m_pResultSet->getString(colIndex));
		case sql::DataType::BINARY:
			return AnyType(Blob(m_pResultSet->getBlob(colIndex)));
		case sql::DataType::VARCHAR:
			return AnyType(m_pResultSet->getString(colIndex));
		case sql::DataType::VARBINARY:
			return AnyType(Blob(m_pResultSet->getBlob(colIndex)));
		case sql::DataType::LONGVARCHAR:
			return AnyType(m_pResultSet->getString(colIndex));
		case sql::DataType::LONGVARBINARY:
			return AnyType(Blob(m_pResultSet->getBlob(colIndex)));
		case sql::DataType::TIMESTAMP:
		{
			Timestamp t = GetTimestamp(colIndex);
			return AnyType(t);
		}
		case sql::DataType::DATE:
			return AnyType(Date(m_pResultSet->getInt(colIndex)));
		case sql::DataType::TIME:
		case sql::DataType::YEAR:
		case sql::DataType::GEOMETRY:
		case sql::DataType::ENUM:
		case sql::DataType::SET:
		case sql::DataType::SQLNULL:
		default:
			return AnyType();
		}

	}
}

Integer mysql_result_set::GetInt(std::string colName)
{
	return Integer(m_pResultSet->getInt(colName), m_pResultSet->isNull(colName));
}

UInteger mysql_result_set::GetUInt(std::string colName)
{
	return UInteger(m_pResultSet->getUInt(colName),
			m_pResultSet->isNull(colName));
}

Float mysql_result_set::GetFloat(std::string colName)
{
	return Float(m_pResultSet->getDouble(colName),
			m_pResultSet->isNull(colName));
}

Double mysql_result_set::GetDouble(std::string colName)
{
	return Double(m_pResultSet->getDouble(colName),
			m_pResultSet->isNull(colName));
}

std::string mysql_result_set::GetString(std::string colName)
{
	return m_pResultSet->getString(colName);
}

AnyType mysql_result_set::GetObject(std::string colName)
{
	return GetObject(GetColumnIndex(colName));
}

Date mysql_result_set::GetDate(std::string colName)
{
	return Date();//new MySqlDate(m_pResultSet->getDate(colIndex));
}

Timestamp mysql_result_set::GetTimestamp(std::string colName)
{
	Timestamp ts;
	std::string timestamp = m_pResultSet->getString(colName);
	ts.FromText(timestamp, "%Y-%m-%d %H:%M:%S");
	return ts;
}

Blob mysql_result_set::GetBlob(std::string colName)
{
	return Blob(m_pResultSet->getBlob(colName));
}

Clob mysql_result_set::GetClob(std::string colName)
{
	return Clob(m_pResultSet->getBlob(colName));
}

int mysql_result_set::GetColumnCount()
{
	sql::ResultSetMetaData *pMetaData = m_pResultSet->getMetaData();
	int nColumnCount = pMetaData->getColumnCount();

	return nColumnCount;
}

std::string mysql_result_set::GetColumnName(unsigned int colIndex)
{
	sql::ResultSetMetaData *pMetaData = m_pResultSet->getMetaData();

	return pMetaData->getColumnName(colIndex);
}

unsigned int mysql_result_set::GetColumnIndex(std::string colName)
{
	sql::ResultSetMetaData *pMetaData = m_pResultSet->getMetaData();
	unsigned int nColumnCount = pMetaData->getColumnCount();

	for (unsigned int i = 0; i < nColumnCount; i++)
	{
		if (pMetaData->getColumnName(i).asStdString() == colName)
			return i;
	}
	throw sql_exception(DATABASE_RESULTSET_WRONGCOL, "Wrong column name:%s", colName.c_str());
}

bool mysql_result_set::IsNull(unsigned int colIndex) const
{
	return m_pResultSet->isNull(colIndex);
}
}
