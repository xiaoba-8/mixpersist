/*
 * i_result_set.cpp
 *
 *  Created on: Mar 25, 2018
 *      Author: xiaoba-8
 */

#include <mix/database/i_result_set.h>

namespace mix
{

template <>
void GetValue<char>(i_result_set *pResult, unsigned int paramIndex, char &x)
{
	std::string result = pResult->GetString(paramIndex);
	if (result.size() == 1)
		x = result.c_str()[0];
	else
		x = 0;
}

template <>
void GetValue<int>(i_result_set *pResult, unsigned int paramIndex, int &x)
{
	x = pResult->GetInt(paramIndex);
}

template <>
void GetValue<bool>(i_result_set *pResult, unsigned int paramIndex, bool &x)
{
	x = pResult->GetInt(paramIndex);
}

template <>
void GetValue<unsigned int>(i_result_set *pResult, unsigned int paramIndex, unsigned int &x)
{
	x = pResult->GetUInt(paramIndex);
}

template <>
void GetValue<unsigned long>(i_result_set *pResult, unsigned int paramIndex, unsigned long &x)
{
	x = pResult->GetUInt(paramIndex);
}

template <>
void GetValue<float>(i_result_set *pResult, unsigned int paramIndex, float &x)
{
	x = pResult->GetDouble(paramIndex);
}

template <>
void GetValue<double>(i_result_set *pResult, unsigned int paramIndex, double &x)
{
	x = pResult->GetDouble(paramIndex);
}

template <>
void GetValue<Integer>(i_result_set *pResult, unsigned int paramIndex, Integer &x)
{
	x = pResult->GetInt(paramIndex);
}

template <>
void GetValue<Long>(i_result_set *pResult, unsigned int paramIndex, Long &x)
{
	x = pResult->GetInt(paramIndex);
}

template <>
void GetValue<UInt64>(i_result_set *pResult, unsigned int paramIndex, UInt64 &x)
{
	x = pResult->GetUInt64(paramIndex);
}

template <>
void GetValue<UInteger>(i_result_set *pResult, unsigned int paramIndex, UInteger &x)
{
	x = pResult->GetUInt(paramIndex);
}

template <>
void GetValue<Float>(i_result_set *pResult, unsigned int paramIndex, Float &x)
{
	x = pResult->GetFloat(paramIndex);
}

template <>
void GetValue<Double>(i_result_set *pResult, unsigned int paramIndex, Double &x)
{
	x = pResult->GetDouble(paramIndex);
}

template <>
void GetValue<std::string>(i_result_set *pResult, unsigned int paramIndex, std::string &x)
{
	x = pResult->GetString(paramIndex);
}

template <>
void GetValue<Date>(i_result_set *pResult, unsigned int paramIndex, Date &x)
{
	x = pResult->GetDate(paramIndex);
}

template <>
void GetValue<Timestamp>(i_result_set *pResult, unsigned int paramIndex, Timestamp &x)
{
	x = pResult->GetTimestamp(paramIndex);
}

template <>
void GetValue<Blob>(i_result_set *pResult, unsigned int paramIndex, Blob &x)
{
	x = pResult->GetBlob(paramIndex);
}

template <>
void GetValue<Clob>(i_result_set *pResult, unsigned int paramIndex, Clob &x)
{
	x = pResult->GetClob(paramIndex);
}

}
