/*
 * GUIDGenerator.h
 *
 *  Created on: 2018-6-7
 *      Author: xiaoba-8
 */

#ifndef GUIDGENERATOR_H_
#define GUIDGENERATOR_H_

namespace mix
{

class GUIDGenerator
{
private:
	GUIDGenerator();
public:
	virtual ~GUIDGenerator();

	static GUIDGenerator *SGetInstance();

	std::string NextUUID();

private:
	void Format(int val, char *dst);
	void Format(short val, char *dst);
	int GetIP();
	int GetPid();
	struct timeval GetTimeInMillis();
	short GetCount();
private:
	static GUIDGenerator *s_pInstance;

	short	m_count;

	int m_ip;
	int m_pid;
};

}

#endif /* GUIDGENERATOR_H_ */
