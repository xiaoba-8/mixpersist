/*
 * i_result_set.h
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#ifndef IRESULTSET_H_
#define IRESULTSET_H_

#include <iostream>
#include "dbdatas.h"

namespace mix
{

class i_result_set
{
public:
	virtual ~i_result_set() {}

	virtual bool Next() = 0;

	virtual void Close() = 0;

	virtual Integer GetInt(unsigned int colIndex) = 0;
	virtual UInteger GetUInt(unsigned int colIndex) = 0;
	virtual UInt64 GetUInt64(unsigned int paramIndex) = 0;
	virtual Float GetFloat(unsigned int colIndex) = 0;
	virtual Double GetDouble(unsigned int colIndex) = 0;
	virtual std::string GetString(unsigned int colIndex) = 0;
	virtual AnyType GetObject(unsigned int colIndex) = 0;

	virtual Date GetDate(unsigned int colIndex) = 0;
	virtual Timestamp GetTimestamp(unsigned int colIndex) = 0;
	virtual Blob GetBlob(unsigned int colIndex) = 0;
	virtual Clob GetClob(unsigned int colIndex) = 0;

	virtual Integer GetInt(std::string colName) = 0;
	virtual UInteger GetUInt(std::string colName) = 0;
	virtual Float GetFloat(std::string colName) = 0;
	virtual Double GetDouble(std::string colName) = 0;
	virtual std::string GetString(std::string colName) = 0;
	virtual AnyType GetObject(std::string colName) = 0;

	virtual Date GetDate(std::string colName) = 0;
	virtual Timestamp GetTimestamp(std::string colName) = 0;
	virtual Blob GetBlob(std::string colName) = 0;
	virtual Clob GetClob(std::string colName) = 0;

	virtual int GetColumnCount() = 0;
	virtual std::string GetColumnName(unsigned int colIndex) = 0;

	virtual unsigned int GetColumnIndex(std::string colName) = 0;

	virtual bool IsNull(unsigned int colIndex) const = 0;
};

template <typename T>
void GetValue(i_result_set *pResult, unsigned int paramIndex, T &x)
{
	std::cout << "template GetValue & is called " << x << std::endl;
}

template <typename T>
void GetValue(i_result_set *pResult, unsigned int paramIndex, T *x)
{
	std::cout << "template GetValue * is called " << x << std::endl;
}

template <>
void GetValue<char>(i_result_set *pResult, unsigned int paramIndex, char &x);

template <>
void GetValue<bool>(i_result_set *pResult, unsigned int paramIndex, bool &x);

template <>
void GetValue<int>(i_result_set *pResult, unsigned int paramIndex, int &x);

template <>
void GetValue<long>(i_result_set *pResult, unsigned int paramIndex, long &x);

template <>
void GetValue<uint64_t>(i_result_set *pResult, unsigned int paramIndex, uint64_t &x);

template <>
void GetValue<unsigned int>(i_result_set *pResult, unsigned int paramIndex, unsigned int &x);

template <>
void GetValue<unsigned long>(i_result_set *pResult, unsigned int paramIndex, unsigned long &x);

template <>
void GetValue<float>(i_result_set *pResult, unsigned int paramIndex, float &x);

template <>
void GetValue<double>(i_result_set *pResult, unsigned int paramIndex, double &x);

template <>
void GetValue<Integer>(i_result_set *pResult, unsigned int paramIndex, Integer &x);

template <>
void GetValue<Long>(i_result_set *pResult, unsigned int paramIndex, Long &x);

template <>
void GetValue<UInt64>(i_result_set *pResult, unsigned int paramIndex, UInt64 &x);

template <>
void GetValue<UInteger>(i_result_set *pResult, unsigned int paramIndex, UInteger &x);

template <>
void GetValue<Float>(i_result_set *pResult, unsigned int paramIndex, Float &x);

template <>
void GetValue<Double>(i_result_set *pResult, unsigned int paramIndex, Double &x);

template <>
void GetValue<std::string>(i_result_set *pResult, unsigned int paramIndex, std::string &x);

template <>
void GetValue<Date>(i_result_set *pResult, unsigned int paramIndex, Date &x);

template <>
void GetValue<Timestamp>(i_result_set *pResult, unsigned int paramIndex, Timestamp &x);

template <>
void GetValue<Blob>(i_result_set *pResult, unsigned int paramIndex, Blob &x);
template <>
void GetValue<Clob>(i_result_set *pResult, unsigned int paramIndex, Clob &x);

}

#endif /* IRESULTSET_H_ */
