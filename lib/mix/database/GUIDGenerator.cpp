/*
 * GUIDGenerator.cpp
 *
 *  Created on: 2018-6-7
 *      Author: xiaoba-8
 */

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <bits/local_lim.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <sstream>
#include <mix/database/GUIDGenerator.h>

#include "db_mutex.h"

namespace mix
{

GUIDGenerator *GUIDGenerator::s_pInstance = NULL;

static db_mutex s_mutex;

GUIDGenerator::GUIDGenerator() : m_count(0), m_ip(0), m_pid(0)
{

}

GUIDGenerator::~GUIDGenerator()
{

}

GUIDGenerator *GUIDGenerator::SGetInstance()
{
	if (s_pInstance == NULL)
	{
		s_pInstance = new GUIDGenerator();
	}

	return s_pInstance;
}

void GUIDGenerator::Format(int val, char *dst)
{
	sprintf(dst, "%08x", val);
}

void GUIDGenerator::Format(short val, char *dst)
{
	sprintf(dst, "%04x", val);
}

int GUIDGenerator::GetIP()
{
	if (m_ip == 0)
	{
		char host[HOST_NAME_MAX+1];

		int len = gethostname(host, HOST_NAME_MAX);

		if (len == 0)
		{
			struct hostent *pEnt;
			if ((pEnt = gethostbyname(host)) != NULL)
			{
				m_ip = ((struct in_addr *)pEnt->h_addr)->s_addr;
			}
		}
	}

	return m_ip;
}

int GUIDGenerator::GetPid()
{
	if (m_pid == 0)
	{
		m_pid = getpid();
	}

	return m_pid;
}

struct timeval GUIDGenerator::GetTimeInMillis()
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);

	return tv;
}

short GUIDGenerator::GetCount()
{
	short count;

	s_mutex.lock();

	m_count ++;
	if (m_count < 0)
		m_count = 0;

	count = m_count;
	s_mutex.unlock();

	return count;
}

std::string GUIDGenerator::NextUUID()
{
	struct timeval tv = GetTimeInMillis();
	char uuid[50];
	int n = 0;

	Format((int)GetIP(), uuid + n);
	n += sizeof(int)*2;

	Format((int)GetPid(), uuid + n);
	n += sizeof(int)*2;

	Format((short)(tv.tv_sec & 0x0ff), uuid + n);
	n += sizeof(short)*2;

	Format((int)tv.tv_usec, uuid + n);
	n += sizeof(int)*2;

	Format((short)GetCount(), uuid + n);
	n += sizeof(short)*2;

	uuid[n] = 0;
	return uuid;
}

}

