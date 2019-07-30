/*
 * database_factory.h
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 *
 */

#ifndef DATABASEFACTORY_H_
#define DATABASEFACTORY_H_

#include <string>
#include <map>
#include "i_creater.h"

namespace mix
{

class database_factory
{
private:
	static database_factory *m_pInstance;

	std::map<std::string, i_creater *> m_createrMap;
	std::string m_defaultId;

	database_factory();
public:
	virtual ~database_factory();

	static database_factory *SGetInstance();

	void Register(std::string, i_creater *);
	void Unregister(std::string id);

	void SetDefaultCreater(std::string);

	i_creater *GetCreater(std::string);
	i_creater *GetDefaultCreater();

	void DestroyCreater();

	void Reset();
};

}
#endif /* DATABASEFACTORY_H_ */
