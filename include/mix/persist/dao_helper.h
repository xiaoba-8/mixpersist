/*
 * dao_helper.h
 *
 *  Created on: 2018-5-3
 *      Author: xiaoba-8
 */

#ifndef DAOIMPL_H_
#define DAOIMPL_H_

#include "../database/idbc.h"
#include "persist.hpp"

namespace mix
{

class dao_helper
{
protected:
	PersistDao m_dao;

public:
	dao_helper(std::string dbname = "");
	virtual ~dao_helper();

	template<typename T>
	int Insert(T &entity)
	{
		return GetDao<T, typename T::DefType>().Insert(entity);
	}

	template<typename T>
	int Update(T entity)
	{
		return GetDao<T, typename T::DefType>().Update(entity);
	}

	template<typename... _Args>
	int GetCount(std::string sql, _Args... args)
	{
		return m_dao.GetCount(sql, args...);
	}

	template<typename T>
	int GetEntityByKey(T &entity)
	{
		return GetDao<T, typename T::DefType>().GetEntityByKey(entity);
	}

	template<typename T, typename... _Args>
	int GetEntityByCondition(T &entity, std::string cond, _Args... args)
	{
		return GetDao<T, typename T::DefType>().GetEntityByCondition(entity, cond, args...);
	}

	template<typename T>
	void SearchEntityByCondition(std::string cond, std::vector<T*> &result, int first = 0, int size = 0)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition(cond, result, true, first, size);
	}

	template<typename T>
	void SearchEntityByCondition(std::string cond, i_search_process *pProcess, int first = 0, int size = 0)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition<T>(cond, pProcess, true, first, size);
	}

	template<typename T, typename... _Args>
	void SearchEntityByCondition(std::string cond, std::vector<T *> &result, int first, int size, _Args... args)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition(cond, result, true, first, size, args...);
	}

	template<typename T, typename... _Args>
	void SearchEntityByCondition(std::string cond, i_search_process *pProcess, int first, int size, _Args... args)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition<T>(cond, pProcess, true, first, size, args...);
	}

	template<typename T>
	void SearchEntityWithoutLobByCondition(std::string cond, std::vector<T*> &result, int first = 0, int size = 0)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition(cond, result, false, first, size);
	}

	template<typename T>
	void SearchEntityWithoutLobByCondition(std::string cond, i_search_process *pProcess, int first = 0, int size = 0)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition<T>(cond, pProcess, false, first, size);
	}

	template<typename T, typename... _Args>
	void SearchEntityWithoutLobByCondition(std::string cond, std::vector<T *> &result, int first, int size, _Args... args)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition(cond, result, false, first, size, args...);
	}

	template<typename T, typename... _Args>
	void SearchEntityWithoutLobByCondition(std::string cond, i_search_process *pProcess, int first, int size, _Args... args)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition<T>(cond, pProcess, false, first, size, args...);
	}


	template<typename T>
	void SearchEntityByCondition(std::string cond, std::vector<T *> &result, std::vector<AnyType> &param, int first, int size)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition(cond, result, param, true, first, size);
	}

	template<typename T>
	void SearchEntityByCondition(std::string cond, i_search_process *pProcess, std::vector<AnyType> &param, int first, int size)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition<T>(cond, pProcess, param, true, first, size);
	}

	template<typename T>
	void SearchEntityWithoutLobByCondition(std::string cond, std::vector<T *> &result, std::vector<AnyType> &param, int first, int size)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition(cond, result, param, false, first, size);
	}

	template<typename T>
	void SearchEntityWithoutLobByCondition(std::string cond, i_search_process *pProcess, std::vector<AnyType> &param, int first, int size)
	{
		return GetDao<T, typename T::DefType>().SearchEntityByCondition<T>(cond, pProcess, param, false, first, size);
	}

	int Execute(std::string sql);
	std::vector<std::vector<AnyType> > Search(std::string sql, int first, int size);

	void Search(std::string sql, i_result_set_process *pProcess, int first, int size);
	void Search(std::string sql, i_result_set_process *pProcess, std::vector<AnyType> &param, int first, int size);
protected:
	template<typename T, typename DefT>
	Dao<DefT> &GetDao();
};

}

#endif /* DAOIMPL_H_ */
