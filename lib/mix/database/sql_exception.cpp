/*
 * sql_exception.cpp
 *
 *  Created on: 2018-4-2
 *      Author: xiaoba-8
 */

#include <mix/database/sql_exception.h>

#include <stdexcept>
#include <stdio.h>
#include <stdarg.h>

namespace mix
{

sql_exception::sql_exception() : m_errno(0)
{

}

sql_exception::sql_exception(int errorno, const char *format, ...) :
				m_errno(errorno)
{
	va_list list;
	va_start(list, format);
	char msg[512];
	vsprintf(msg, format, list);
	va_end(list);

	m_what.assign(msg);
}

sql_exception::~sql_exception() throw ()
{
}

const char *sql_exception::what() const throw ()
{
	return m_what.c_str();
}

int sql_exception::GetErrNo()
{
	return m_errno;
}

}
