/*
 * sql_exception.h
 *
 *  Created on: 2018-4-2
 *      Author: xiaoba-8
 *
 */

#ifndef SQLEXCEPTION_H_
#define SQLEXCEPTION_H_

#include <string>

namespace mix
{

class sql_exception
{
public:
    explicit sql_exception();
    explicit sql_exception(int errorno, const char *format, ...);
	virtual ~sql_exception() throw ();

	virtual const char * what() const throw();
	virtual int GetErrNo();
protected:
	std::string m_what;
	int m_errno;

};

}

#endif /* SQLEXCEPTION_H_ */
