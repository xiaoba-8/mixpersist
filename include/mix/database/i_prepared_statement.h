/*
 * i_prepared_statement.h
 *
 *  Created on: Mar 29, 2018
 *      Author: xiaoba-8
 */

#ifndef IPREPAREDSTATEMENT_H_
#define IPREPAREDSTATEMENT_H_

#include "dbdatas.h"
#include "i_statement.h"

namespace mix
{

class i_prepared_statement : public i_statement
{
public:
	virtual ~i_prepared_statement() {}

	virtual i_result_set *ExecuteQuery() = 0;

	virtual int ExecuteUpdate() = 0;

	virtual void SetNull(unsigned int paramIndex, int type) = 0;
	virtual void SetInt(unsigned int paramIndex, Integer x) = 0;
	virtual void SetUInt64(unsigned int paramIndex, UInt64 x) = 0;
	virtual void SetUInt(unsigned int paramIndex, UInteger x) = 0;
	virtual void SetFloat(unsigned int paramIndex, Float x) = 0;
	virtual void SetDouble(unsigned int paramIndex, Double x) = 0;
	virtual void SetString(unsigned int paramIndex,	const std::string &x) = 0;
	virtual void SetDate(unsigned int paramIndex, const Date &x) = 0;
	virtual void SetTimestamp(unsigned int paramIndex, const Timestamp &x) = 0;
	virtual void SetBlob(unsigned int paramIndex, Blob &x) = 0;
	virtual void SetClob(unsigned int paramIndex, Clob &x) = 0;

	virtual bool NeedUpdateBlob() = 0;
};

template <typename T>
void SetValue(i_prepared_statement *pStatement, unsigned int paramIndex, T x)
{
	std::cout << "The template function for setvalue is called " << x << std::endl;
}

template <>
void SetValue<char>(i_prepared_statement *pStatement, unsigned int paramIndex, char x);

template <>
void SetValue<int>(i_prepared_statement *pStatement, unsigned int paramIndex, int x);

template <>
void SetValue<bool>(i_prepared_statement *pStatement, unsigned int paramIndex, bool x);

template <>
void SetValue<long>(i_prepared_statement *pStatement, unsigned int paramIndex, long x);

template <>
void SetValue<uint64_t>(i_prepared_statement *pStatement, unsigned int paramIndex, uint64_t x);

template <>
void SetValue<unsigned int>(i_prepared_statement *pStatement, unsigned int paramIndex, unsigned int x);

template <>
void SetValue<float>(i_prepared_statement *pStatement, unsigned int paramIndex, float x);

template <>
void SetValue<double>(i_prepared_statement *pStatement, unsigned int paramIndex, double x);

template <>
void SetValue<Integer>(i_prepared_statement *pStatement, unsigned int paramIndex, Integer x);

template <>
void SetValue<Long>(i_prepared_statement *pStatement, unsigned int paramIndex, Long x);

template <>
void SetValue<UInt64>(i_prepared_statement *pStatement, unsigned int paramIndex, UInt64 x);

template <>
void SetValue<UInteger>(i_prepared_statement *pStatement, unsigned int paramIndex, UInteger x);

template <>
void SetValue<Float>(i_prepared_statement *pStatement, unsigned int paramIndex, Float x);

template <>
void SetValue<Double>(i_prepared_statement *pStatement, unsigned int paramIndex, Double x);

template <>
void SetValue<const std::string>(i_prepared_statement *pStatement, unsigned int paramIndex, const std::string x);

template <>
void SetValue<const char *>(i_prepared_statement *pStatement, unsigned int paramIndex, const char *x);

template <>
void SetValue<const Date>(i_prepared_statement *pStatement, unsigned int paramIndex, const Date x);

template <>
void SetValue<const Timestamp>(i_prepared_statement *pStatement, unsigned int paramIndex, const Timestamp x);

template <>
void SetValue<std::string>(i_prepared_statement *pStatement, unsigned int paramIndex, std::string x);

template <>
void SetValue<char *>(i_prepared_statement *pStatement, unsigned int paramIndex, char *x);

template <>
void SetValue<Date >(i_prepared_statement *pStatement, unsigned int paramIndex, Date x);

template <>
void SetValue<Timestamp >(i_prepared_statement *pStatement, unsigned int paramIndex, Timestamp x);

template <>
void SetValue<Blob>(i_prepared_statement *pStatement, unsigned int paramIndex, Blob x);
template <>
void SetValue<Clob>(i_prepared_statement *pStatement, unsigned int paramIndex, Clob x);
}

#endif /* IPREPAREDSTATEMENT_H_ */
