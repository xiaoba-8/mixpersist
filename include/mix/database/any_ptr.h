/*
 * any_ptr.h
 *
 *  Created on: 2018-5-5
 *      Author: xiaoba-8
 */

#ifndef ANYPTR_H_
#define ANYPTR_H_

#include <stddef.h>

namespace mix
{

template<class Data>
class any_ptr
{
protected:
	Data *m_pData;
public:
	any_ptr()
	{
		m_pData = NULL;
	}
	any_ptr(Data *pData) :
		m_pData(pData)
	{
	}
	virtual ~any_ptr()
	{
		delete m_pData;
	}

	Data * operator->()
	{
		return m_pData;
	}
	Data & operator*()
	{
		return *m_pData;
	}

	Data * Value()
	{
		return m_pData;
	}

	void ResetValue(Data *pData)
	{
		if (m_pData != NULL)
			delete m_pData;
		m_pData = pData;
	}

private:
	any_ptr(const any_ptr&);
	any_ptr& operator =(const any_ptr&);
};

}

#endif /* ANYPTR_H_ */
