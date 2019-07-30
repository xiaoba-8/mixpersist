/*
 * i_prepared_statement.cpp
 *
 *  Created on: Mar 29, 2018
 *      Author: xiaoba-8
 */

#include <mix/database/i_prepared_statement.h>

namespace mix
{

template <>
void SetValue<char>(i_prepared_statement *pStatement, unsigned int paramIndex, char x)
{
	std::string lx = " ";
	lx[0] = x;
	pStatement->SetString(paramIndex, lx);
}

template <>
void SetValue<int>(i_prepared_statement *pStatement, unsigned int paramIndex, int x)
{
	pStatement->SetInt(paramIndex, x);
}

template <>
void SetValue<bool>(i_prepared_statement *pStatement, unsigned int paramIndex, bool x)
{
	pStatement->SetInt(paramIndex, (int)x);
}

template <>
void SetValue<uint64_t>(i_prepared_statement *pStatement, unsigned int paramIndex, uint64_t x)
{
	pStatement->SetUInt64(paramIndex, x);
}

template <>
void SetValue<unsigned int>(i_prepared_statement *pStatement, unsigned int paramIndex, unsigned int x)
{
	pStatement->SetUInt(paramIndex, x);
}

template <>
void SetValue<float>(i_prepared_statement *pStatement, unsigned int paramIndex, float x)
{
	pStatement->SetFloat(paramIndex, x);
}

template <>
void SetValue<double>(i_prepared_statement *pStatement, unsigned int paramIndex, double x)
{
	pStatement->SetDouble(paramIndex, x);
}

template <>
void SetValue<Integer>(i_prepared_statement *pStatement, unsigned int paramIndex, Integer x)
{
	SetValue<int>(pStatement, paramIndex, x.Value());
}

template <>
void SetValue<UInt64>(i_prepared_statement *pStatement, unsigned int paramIndex, UInt64 x)
{
	pStatement->SetUInt64(paramIndex, x);
}

template <>
void SetValue<UInteger>(i_prepared_statement *pStatement, unsigned int paramIndex, UInteger x)
{
	SetValue<unsigned int>(pStatement, paramIndex, x.Value());
}

template <>
void SetValue<Float>(i_prepared_statement *pStatement, unsigned int paramIndex, Float x)
{
	SetValue<float>(pStatement, paramIndex, x.Value());
}

template <>
void SetValue<Double>(i_prepared_statement *pStatement, unsigned int paramIndex, Double x)
{
	SetValue<double>(pStatement, paramIndex, x.Value());
}

template <>
void SetValue<const std::string >(i_prepared_statement *pStatement, unsigned int paramIndex, const std::string x)
{
	pStatement->SetString(paramIndex, x);
}

template <>
void SetValue<const char *>(i_prepared_statement *pStatement, unsigned int paramIndex, const char *x)
{
	pStatement->SetString(paramIndex, x);
}

template <>
void SetValue<const Date>(i_prepared_statement *pStatement, unsigned int paramIndex, const Date x)
{
	pStatement->SetDate(paramIndex, x);
}

template <>
void SetValue<const Timestamp>(i_prepared_statement *pStatement, unsigned int paramIndex, const Timestamp x)
{
	pStatement->SetTimestamp(paramIndex, x);
}

template <>
void SetValue<std::string>(i_prepared_statement *pStatement, unsigned int paramIndex, std::string x)
{
	pStatement->SetString(paramIndex, x);
}

template <>
void SetValue<char *>(i_prepared_statement *pStatement, unsigned int paramIndex, char *x)
{
	pStatement->SetString(paramIndex, x);
}

template <>
void SetValue<Date>(i_prepared_statement *pStatement, unsigned int paramIndex, Date x)
{
	pStatement->SetDate(paramIndex, x);
}

template <>
void SetValue<Timestamp>(i_prepared_statement *pStatement, unsigned int paramIndex, Timestamp x)
{
	pStatement->SetTimestamp(paramIndex, x);
}

template <>
void SetValue<Blob >(i_prepared_statement *pStatement, unsigned int paramIndex, Blob x)
{
	pStatement->SetBlob(paramIndex, x);
}

template <>
void SetValue<Clob >(i_prepared_statement *pStatement, unsigned int paramIndex, Clob x)
{
	pStatement->SetClob(paramIndex, x);
}

}

