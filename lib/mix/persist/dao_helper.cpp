/*
 * dao_helper.cpp
 *
 *  Created on: 2018-5-3
 *      Author: xiaoba-8
 */

#include <mix/persist/dao_helper.h>


namespace mix
{

dao_helper::dao_helper(std::string dbname) : m_dao(dbname)
{

}

dao_helper::~dao_helper()
{
}

int dao_helper::Execute(std::string sql)
{
	return m_dao.Execute(sql);
}

std::vector<std::vector<AnyType> > dao_helper::Search(std::string sql, int first, int size)
{
	return m_dao.Search(sql, first, size);
}

void dao_helper::Search(std::string sql, i_result_set_process *pProcess, int first, int size)
{
	m_dao.Search(sql, pProcess, first, size);
}

void dao_helper::Search(std::string sql, i_result_set_process *pProcess, std::vector<AnyType> &param, int first, int size)
{
	m_dao.Search(sql, pProcess, param, first, size);
}
}
