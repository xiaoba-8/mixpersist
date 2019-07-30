/*
 * db_mutex.cpp
 *
 *  Created on: 2019-2-8
 *      Author: xiaoba-8
 */

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include "db_mutex.h"

namespace mix
{

#ifdef _WIN32

db_mutex::db_mutex()
{
	m_mutex = CreateMutex(NULL,FALSE,NULL);
}

db_mutex::~db_mutex()
{
	CloseHandle(m_mutex);
}

void db_mutex::lock()
{
	WaitForSingleObject(m_mutex,INFINITE);
}

void db_mutex::unlock()
{
	ReleaseMutex(m_mutex);
}

#else

db_mutex::db_mutex() : m_mutex(PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP)
{
}
db_mutex::~db_mutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void db_mutex::lock()
{
	pthread_mutex_lock(&m_mutex);
}

void db_mutex::unlock()
{
	pthread_mutex_unlock(&m_mutex);
}

#endif

}
