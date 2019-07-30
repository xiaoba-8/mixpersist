/*
 * database_factory.cpp
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#include <mix/database/database_factory.h>

namespace mix
{

database_factory *database_factory::m_pInstance = NULL;

database_factory::database_factory()
{

}

database_factory::~database_factory()
{

}

void database_factory::DestroyCreater()
{
	std::map<std::string, i_creater *>::iterator itr = m_createrMap.begin();

	for (; itr != m_createrMap.end(); ++itr)
	{
		delete (*itr).second;
	}
}

database_factory *database_factory::SGetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new database_factory();
	}
	return m_pInstance;
}

void database_factory::Register(std::string id, i_creater *pCreater)
{
	m_createrMap[id] = pCreater;
}

void database_factory::Unregister(std::string id)
{
	m_createrMap.erase(id);
}

void database_factory::SetDefaultCreater(std::string id)
{
	m_defaultId = id;
}

i_creater *database_factory::GetCreater(std::string id)
{
	if (id == "")
		return GetDefaultCreater();
	else
		return m_createrMap[id];
}

i_creater *database_factory::GetDefaultCreater()
{
	if (m_defaultId.size() > 0)
		return m_createrMap[m_defaultId];

	if (m_createrMap.size() > 0)
		return m_createrMap.begin()->second;
	else
		return NULL;
}

void database_factory::Reset()
{
	std::map<std::string, i_creater *>::iterator itr = m_createrMap.begin();

	for (; itr != m_createrMap.end(); ++itr)
	{
		(*itr).second->Reset();
	}
}
}
