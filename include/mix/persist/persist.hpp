/*
 * persist.hpp
 *
 *  Created on: Mar 21, 2018
 *      Author: xiaoba-8
 */

#ifndef HIBERNATE_HPP_
#define HIBERNATE_HPP_

#include <pthread.h>
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>

#include "../database/any_ptr.h"
#include "../database/dbmapping.h"
#include "../database/GUIDGenerator.h"
#include "../database/idbc.h"
#include "../database/sql_exception.h"

#include "../database/db_errno.h"

namespace mix
{

enum _column_type {COLUMN_NORM, COLUMN_LOB, COLUMN_ALL};

template<typename T, typename Entity>
struct column_def: public _void_def
{
	typedef T value_type;

	ColumnDef m_columnDef;

	T (Entity::*m_get_f)();
	void (Entity::*m_set_f)(T t);

	column_def(const char *columnName, T (Entity::*get_f)(),
			void(Entity::*set_f)(T t), bool isKey = false,
			bool autoincr = false) :
		m_columnDef(ColumnDef(columnName, isKey, autoincr)),
				m_get_f(get_f), m_set_f(set_f)
	{

	}

	std::string toString(T &t)
	{
		std::string ret;
		ret.append(t);
		return ret;
	}

	std::string getValue(Entity &entity)
	{
		T value = (entity.*(m_get_f))();
		return toString(value);
	}
};

template <typename T>
bool isEmpty(T t)
{
	return false;
}

template <>
bool isEmpty<std::string>(std::string t);

template <typename T>
bool isNull(T t)
{
	return false;
}

template <>
bool isNull<Integer>(Integer t);

template <>
bool isNull<UInteger>(UInteger t);

template <>
bool isNull<Long>(Long t);

template <>
bool isNull<Float>(Float t);

template <>
bool isNull<Double>(Double t);


template<typename Type>
bool is_need_update(Type &t)
{
	return false;
}

template<>
bool is_need_update(Blob &blob);

template<>
bool is_need_update(Clob &clob);

template<typename Type>
bool is_lob()
{
	return false;
}

template<>
bool is_lob<Blob>();

template<>
bool is_lob<Clob>();

template<typename TableDef>
bool is_lob(int column)
{
	switch (column)
	{
	case 0:
	{
		return is_lob<typename TableDef::t0_type>();
	}
	case 1:
	{
		return is_lob<typename TableDef::t1_type>();
	}
	case 2:
	{
		return is_lob<typename TableDef::t2_type>();
	}
	case 3:
	{
		return is_lob<typename TableDef::t3_type>();
	}
	case 4:
	{
		return is_lob<typename TableDef::t4_type>();
	}
	case 5:
	{
		return is_lob<typename TableDef::t5_type>();
	}
	case 6:
	{
		return is_lob<typename TableDef::t6_type>();
	}
	case 7:
	{
		return is_lob<typename TableDef::t7_type>();
	}
	case 8:
	{
		return is_lob<typename TableDef::t8_type>();
	}
	case 9:
	{
		return is_lob<typename TableDef::t9_type>();
	}
	case 10:
	{
		return is_lob<typename TableDef::t10_type>();
	}
	case 11:
	{
		return is_lob<typename TableDef::t11_type>();
	}
	case 12:
	{
		return is_lob<typename TableDef::t12_type>();
	}
	case 13:
	{
		return is_lob<typename TableDef::t13_type>();
	}
	case 14:
	{
		return is_lob<typename TableDef::t14_type>();
	}
	case 15:
	{
		return is_lob<typename TableDef::t15_type>();
	}
	case 16:
	{
		return is_lob<typename TableDef::t16_type>();
	}
	case 17:
	{
		return is_lob<typename TableDef::t17_type>();
	}
	case 18:
	{
		return is_lob<typename TableDef::t18_type>();
	}
	case 19:
	{
		return is_lob<typename TableDef::t19_type>();
	}
	case 20:
	{
		return is_lob<typename TableDef::t20_type>();
	}
	case 21:
	{
		return is_lob<typename TableDef::t21_type>();
	}
	case 22:
	{
		return is_lob<typename TableDef::t22_type>();
	}
	case 23:
	{
		return is_lob<typename TableDef::t23_type>();
	}
	case 24:
	{
		return is_lob<typename TableDef::t24_type>();
	}
	case 25:
	{
		return is_lob<typename TableDef::t25_type>();
	}
	case 26:
	{
		return is_lob<typename TableDef::t26_type>();
	}
	case 27:
	{
		return is_lob<typename TableDef::t27_type>();
	}
	case 28:
	{
		return is_lob<typename TableDef::t28_type>();
	}
	case 29:
	{
		return is_lob<typename TableDef::t29_type>();
	}
	case 30:
	{
		return is_lob<typename TableDef::t30_type>();
	}
	case 31:
	{
		return is_lob<typename TableDef::t31_type>();
	}
	case 32:
	{
		return is_lob<typename TableDef::t32_type>();
	}
	case 33:
	{
		return is_lob<typename TableDef::t33_type>();
	}
	case 34:
	{
		return is_lob<typename TableDef::t34_type>();
	}
	case 35:
	{
		return is_lob<typename TableDef::t35_type>();
	}
	case 36:
	{
		return is_lob<typename TableDef::t36_type>();
	}
	case 37:
	{
		return is_lob<typename TableDef::t37_type>();
	}
	case 38:
	{
		return is_lob<typename TableDef::t38_type>();
	}
	case 39:
	{
		return is_lob<typename TableDef::t39_type>();
	}
	case 40:
	{
		return is_lob<typename TableDef::t40_type>();
	}
	}

	return false;
}

template <typename T>
bool SetValueBack(T &t, std::string v)
{
	return false;
}

template <>
bool SetValueBack<std::string>(std::string &t, std::string v);

template<int N, typename T0 = int, typename T1 = int,
		typename T2 = int, typename T3 = int,
		typename T4 = int, typename T5 = int,
		typename T6 = int, typename T7 = int,
		typename T8 = int, typename T9 = int,
		typename T10 = int, typename T11 = int,
		typename T12 = int, typename T13 = int,
		typename T14 = int, typename T15 = int,
		typename T16 = int, typename T17 = int,
		typename T18 = int, typename T19 = int,
		typename T20 = int, typename T21 = int,
		typename T22 = int, typename T23 = int,
		typename T24 = int, typename T25 = int,
		typename T26 = int, typename T27 = int,
		typename T28 = int, typename T29 = int,
		typename T30 = int, typename T31 = int,
		typename T32 = int, typename T33 = int,
		typename T34 = int, typename T35 = int,
		typename T36 = int, typename T37 = int,
		typename T38 = int, typename T39 = int,
		typename T40 = int>
struct entity_def
{
	std::string m_tableName;
	_void_def *m_columns[N];

	static const int m_colNum = N;

	typedef T0 t0_type;
	typedef T1 t1_type;
	typedef T2 t2_type;
	typedef T3 t3_type;
	typedef T4 t4_type;
	typedef T5 t5_type;
	typedef T6 t6_type;
	typedef T7 t7_type;
	typedef T8 t8_type;
	typedef T9 t9_type;
	typedef T10 t10_type;
	typedef T11 t11_type;
	typedef T12 t12_type;
	typedef T13 t13_type;
	typedef T14 t14_type;
	typedef T15 t15_type;
	typedef T16 t16_type;
	typedef T17 t17_type;
	typedef T18 t18_type;
	typedef T19 t19_type;
	typedef T20 t20_type;
	typedef T21 t21_type;
	typedef T22 t22_type;
	typedef T23 t23_type;
	typedef T24 t24_type;
	typedef T25 t25_type;
	typedef T26 t26_type;
	typedef T27 t27_type;
	typedef T28 t28_type;
	typedef T29 t29_type;
	typedef T30 t30_type;
	typedef T31 t31_type;
	typedef T32 t32_type;
	typedef T33 t33_type;
	typedef T34 t34_type;
	typedef T35 t35_type;
	typedef T36 t36_type;
	typedef T37 t37_type;
	typedef T38 t38_type;
	typedef T39 t39_type;
	typedef T40 t40_type;

	~entity_def()
	{
		for (int i = 0; i < N; i++)
		{
			delete m_columns[i];
		}
	}
};

template <typename T, bool should>
struct add_ {
	std::string operator() (T value)
	{
		std::stringstream s2;
		if (should)
			s2 << "'" << value << "'";
		else
			s2 << value;

		s2.flush();

		std::string ret;
		ret.append(s2.str());
		return ret;
	}
};


class i_result_set_process
{
public:
	virtual ~i_result_set_process() {}

	virtual void Process(i_result_set *pResultSet) = 0;
};

class PersistDao
{
public:
	PersistDao(std::string dbname = "");
	virtual ~PersistDao();

	template<typename... _Args>
	int Execute(std::string sql, _Args... args)
	{
		i_connection *pConn = NULL;
		int nResult = 0;
		std::string message;
		int errcode = 0;

		try
		{
			pConn = transaction_manager::SGetTransactionManager(m_dbname)->GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);

			message = "PersistDao::Execute :" + sql;
			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		try
		{
    		any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql));

    		int nIndex = 1;
    		SetStatementValue(pStmt.Value(), nIndex, args...);

			nResult = pStmt->ExecuteUpdate();
			pStmt->Close();

			transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);

		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);

			message = "PersistDao::Execute :" + sql;
			message.append(e.what());
			errcode = e.GetErrNo();

		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());
		return nResult;
	}

	void Search(std::string sql, i_result_set_process *pProcess, std::vector<AnyType> &param, int first, int size)
	{
		i_connection *pConn = NULL;
		std::string message;
		int errcode = 0;

		try
		{
			pConn = transaction_manager::SGetTransactionManager()->GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);

			errcode = e.GetErrNo();
			throw sql_exception(errcode, e.what());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql));

			unsigned int nIndex = 1;
			for (unsigned int i = 0; i < param.size(); i++)
			{
				AnyType &pm = param[i];
				switch (pm.GetType())
				{
				case AnyType::INT:
					SetValue<int>(pStmt.Value(), nIndex++, pm.GetInt());
					break;
				case AnyType::CHAR:
					SetValue(pStmt.Value(), nIndex++, pm.GetChar());
					break;
				case AnyType::SHORT:
					SetValue(pStmt.Value(), nIndex++, pm.GetShort());
					break;
				case AnyType::DOUBLE:
					SetValue(pStmt.Value(), nIndex++, pm.GetDouble());
					break;
				case AnyType::FLOAT:
					SetValue(pStmt.Value(), nIndex++, pm.GetFloat());
					break;
				case AnyType::STRING:
					SetValue(pStmt.Value(), nIndex++, pm.GetString());
					break;
				case AnyType::DATE:
					SetValue(pStmt.Value(), nIndex++, pm.GetDate());
					break;
				case AnyType::TIMESTAMP:
					SetValue(pStmt.Value(), nIndex++, pm.GetTimestamp());
					break;
				default:
					break;
				}
			}

			any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

			int nPos = 0;
			while (pRs->Next())
			{
				if (nPos >= first && (size <= 0 || nPos < first + size))
				{
					pProcess->Process(pRs.Value());
				}
				nPos ++;
			}

			pRs->Close();
			pStmt->Close();
			transaction_manager::SGetTransactionManager()->STerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager()->STerminateConnection(pConn);

			errcode = e.GetErrNo();
			message.append(e.what());
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());
	}

	template<typename... _Args>
	void Search(std::string sql, i_result_set_process *pProcess, int first, int size, _Args... args)
	{
		i_connection *pConn = NULL;
		std::string message;
		int errcode = 0;

		try
		{
			pConn = transaction_manager::SGetTransactionManager()->GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);

			errcode = e.GetErrNo();
			message.append(e.what());
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql));

			int nIndex = 1;
			SetStatementValue(pStmt.Value(), nIndex, args...);

			any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

			int nPos = 0;
			while (pRs->Next())
			{
				if (nPos >= first && (size <= 0 || nPos < first + size))
				{
					pProcess->Process(pRs.Value());
				}
				nPos ++;
			}

			pRs->Close();
			pStmt->Close();
			transaction_manager::SGetTransactionManager()->STerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager()->STerminateConnection(pConn);
			errcode = e.GetErrNo();
			message.append(e.what());
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());
	}

	template <typename... _Args>
	int GetCount(std::string sql, _Args... args)
	{
		std::string message;
		int errcode = 0;

		i_connection *pConn = NULL;
		int nCount = 0;

		try
		{
			pConn = transaction_manager::SGetTransactionManager()->GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);

			errcode = e.GetErrNo();
			message.append(e.what());
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql));

    		int nSerial = 1;
    		SetStatementValue(pStmt.Value(), nSerial, args...);

			any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

			if (pRs->Next())
			{
				nCount = pRs->GetInt(1);
			}

			pRs->Close();
			pStmt->Close();
			transaction_manager::SGetTransactionManager()->STerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager()->STerminateConnection(pConn);
			errcode = e.GetErrNo();
			message.append(e.what());
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());

		return nCount;
	}

	int GetCount(std::string sql, std::vector<AnyType> &param)
	{
		std::string message;
		int errcode = 0;

		i_connection *pConn = NULL;
		int nCount = 0;

		try
		{
			pConn = transaction_manager::SGetTransactionManager()->GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);

			errcode = e.GetErrNo();
			message.append(e.what());
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql));

			unsigned int nIndex = 1;
			for (unsigned int i = 0; i < param.size(); i++)
			{
				AnyType &pm = param[i];
				switch (pm.GetType())
				{
				case AnyType::INT:
					SetValue<int>(pStmt.Value(), nIndex++, pm.GetInt());
					break;
				case AnyType::CHAR:
					SetValue(pStmt.Value(), nIndex++, pm.GetChar());
					break;
				case AnyType::SHORT:
					SetValue(pStmt.Value(), nIndex++, pm.GetShort());
					break;
				case AnyType::LONG:
					SetValue(pStmt.Value(), nIndex++, pm.GetLong());
					break;
				case AnyType::DOUBLE:
					SetValue(pStmt.Value(), nIndex++, pm.GetDouble());
					break;
				case AnyType::FLOAT:
					SetValue(pStmt.Value(), nIndex++, pm.GetFloat());
					break;
				case AnyType::STRING:
					SetValue(pStmt.Value(), nIndex++, pm.GetString());
					break;
				case AnyType::DATE:
					SetValue(pStmt.Value(), nIndex++, pm.GetDate());
					break;
				case AnyType::TIMESTAMP:
					SetValue(pStmt.Value(), nIndex++, pm.GetTimestamp());
					break;
				default:
					break;
				}
			}

			any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

			if (pRs->Next())
			{
				nCount = pRs->GetInt(1);
			}

			pRs->Close();
			pStmt->Close();
			transaction_manager::SGetTransactionManager()->STerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager()->STerminateConnection(pConn);
			errcode = e.GetErrNo();
			message.append(e.what());
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());

		return nCount;
	}

	std::vector<std::vector<AnyType> > Search(std::string sql, int first = 0, int size = 0);

    template<typename... _Args>
	std::vector<std::vector<AnyType> > SearchByParameter(std::string sql, int first, int size, _Args... args)
	{
    	i_connection *pConn = NULL;
    	std::string message;
		int errcode = 0;
		std::vector<std::vector<AnyType> > result;

    	try
    	{
    		pConn = transaction_manager::SGetTransactionManager(m_dbname)->GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
    		any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql));

    		int nIndex = 1;
    		SetStatementValue(pStmt.Value(), nIndex, args...);

    		any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

    		int nCount = pRs->GetColumnCount();
    		int nPos = 0;
    		while (pRs->Next())
    		{
    			if (nPos >= first && (size <= 0 || nPos < first + size))
    			{
    				std::vector<AnyType> row;

    				for (int i=0; i < nCount; i++)
    				{
    					AnyType val = pRs->GetObject(i+1);
    					row.push_back(val);
    				}
    				result.push_back(row);
    			}
    			nPos ++;
    		}

    		pRs->Close();
    		pStmt->Close();

    		transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);
		}
    	catch (sql_exception &e)
    	{
    		if (pConn != NULL)
    			transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);

    		message = "PersistDao::Search :" + sql;
			errcode = e.GetErrNo();
			message.append(e.what());
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());

		return result;
	}

    void SetDbname(std::string dbname);
    std::string GetDbName();

protected:
    void SetStatementValue(i_prepared_statement *pStmt, int &index);

    template<typename T, typename... _Args>
    void SetStatementValue(i_prepared_statement *pStmt, int &index, T value, _Args... args)
    {
    	SetValue(pStmt, index++, value);
    	return SetStatementValue(pStmt, index, args...);
    }

    std::string m_dbname;
};

class i_search_process
{
public:
	virtual void Process(void *pData) = 0;
	virtual bool IsCanceled() = 0;
};

template<typename TableDef>
class Dao : public PersistDao
{
private:
	TableDef &m_tableDef;
	/*
	 * 		ALL		 All column
	 * 		KEY		 primary key column/s
	 * 		NORMAL	 other columns
	 */
	enum ColumnType {ALL = 0, KEY = 1, NORMAL = 2};

	template<typename Type, typename Entity>
	void CommonTypeCall(Entity *pEntity, _void_def *sql, int index, _void_def *pColumn,
			void (*f)(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *sql), _column_type colType, bool isRetrieve)
	{
		switch (colType)
		{
		case COLUMN_NORM:
		{
			if (!is_lob<Type>())
			{
				column_def<Type, Entity> *pCol = (column_def<Type, Entity> *)pColumn;
				//f(pCol->m_columnDef, sql);
				f(pCol->m_columnDef, index, is_lob<Type>(), m_tableDef.m_tableName, sql);
			}
			break;
		}
		case COLUMN_LOB:
		{
			if (is_lob<Type>())
			{
				column_def<Type, Entity> *pCol = (column_def<Type, Entity> *)pColumn;
				Type ret = (pEntity->*(pCol->m_get_f))();
				if (!is_need_update(ret))
					return;
				//f(pCol->m_columnDef, sql);
				f(pCol->m_columnDef, index, is_lob<Type>(), m_tableDef.m_tableName, sql);
			}
			else
			{
				column_def<Type, Entity> *pCol = (column_def<Type, Entity> *)pColumn;
				if (pCol->m_columnDef.m_identify)
				{
					//f(pCol->m_columnDef, sql);
					f(pCol->m_columnDef, index, is_lob<Type>(), m_tableDef.m_tableName, sql);
				}
			}
			break;
		}
		case COLUMN_ALL:
		{
			column_def<Type, Entity> *pCol = (column_def<Type, Entity> *)pColumn;
			if (!isRetrieve && is_lob<Type>())
			{
				Type ret = (pEntity->*(pCol->m_get_f))();
				if (!is_need_update(ret))
					return;
			}

			//f(pCol->m_columnDef, sql);
			f(pCol->m_columnDef, index, is_lob<Type>(), m_tableDef.m_tableName, sql);
			break;
		}
		}

		return;
	}

	template<typename Entity>
	void CommonCall(Entity *pEntity, _void_def *sql, int index,
			void (*f)(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *sql), _column_type colType, bool isRetrieve)
	{
		switch (index)
		{
		case 0:
		{
			CommonTypeCall<typename TableDef::t0_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 1:
		{
			CommonTypeCall<typename TableDef::t1_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 2:
		{
			CommonTypeCall<typename TableDef::t2_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 3:
		{
			CommonTypeCall<typename TableDef::t3_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 4:
		{
			CommonTypeCall<typename TableDef::t4_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 5:
		{
			CommonTypeCall<typename TableDef::t5_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 6:
		{
			CommonTypeCall<typename TableDef::t6_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 7:
		{
			CommonTypeCall<typename TableDef::t7_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 8:
		{
			CommonTypeCall<typename TableDef::t8_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 9:
		{
			CommonTypeCall<typename TableDef::t9_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 10:
		{
			CommonTypeCall<typename TableDef::t10_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 11:
		{
			CommonTypeCall<typename TableDef::t11_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 12:
		{
			CommonTypeCall<typename TableDef::t12_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 13:
		{
			CommonTypeCall<typename TableDef::t13_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 14:
		{
			CommonTypeCall<typename TableDef::t14_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 15:
		{
			CommonTypeCall<typename TableDef::t15_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 16:
		{
			CommonTypeCall<typename TableDef::t16_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 17:
		{
			CommonTypeCall<typename TableDef::t17_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 18:
		{
			CommonTypeCall<typename TableDef::t18_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 19:
		{
			CommonTypeCall<typename TableDef::t19_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 20:
		{
			CommonTypeCall<typename TableDef::t20_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 21:
		{
			CommonTypeCall<typename TableDef::t21_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 22:
		{
			CommonTypeCall<typename TableDef::t22_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 23:
		{
			CommonTypeCall<typename TableDef::t23_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 24:
		{
			CommonTypeCall<typename TableDef::t24_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 25:
		{
			CommonTypeCall<typename TableDef::t25_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 26:
		{
			CommonTypeCall<typename TableDef::t26_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 27:
		{
			CommonTypeCall<typename TableDef::t27_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 28:
		{
			CommonTypeCall<typename TableDef::t28_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 29:
		{
			CommonTypeCall<typename TableDef::t29_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 30:
		{
			CommonTypeCall<typename TableDef::t30_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 31:
		{
			CommonTypeCall<typename TableDef::t31_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 32:
		{
			CommonTypeCall<typename TableDef::t32_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 33:
		{
			CommonTypeCall<typename TableDef::t33_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 34:
		{
			CommonTypeCall<typename TableDef::t34_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 35:
		{
			CommonTypeCall<typename TableDef::t35_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 36:
		{
			CommonTypeCall<typename TableDef::t36_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 37:
		{
			CommonTypeCall<typename TableDef::t37_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 38:
		{
			CommonTypeCall<typename TableDef::t38_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 39:
		{
			CommonTypeCall<typename TableDef::t39_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		case 40:
		{
			CommonTypeCall<typename TableDef::t40_type, Entity> (pEntity, sql, index,
					m_tableDef.m_columns[index], f, colType, isRetrieve);
			break;
		}
		}
	}

	template<typename Type, typename Entity>
	void UpdateToNull(Entity &entity, int &index, _void_def *pColumn, std::string &sql, ColumnType type, bool withLob=true)
	{
		if (!withLob)
		{
			if (is_lob<Type>()) return;
		}
		std::string nullStr = "null";

		column_def<Type, Entity> *pCol = (column_def<Type, Entity> *) pColumn;

		switch (type)
		{
		case ALL:
			{
			}
			break;
		case KEY:
			if (!pCol->m_columnDef.m_identify)
			{
				return;
			}
			break;
		case NORMAL:
			if (pCol->m_columnDef.m_identify)
			{
				return;
			}
			break;
		}

		Type ret = (entity.*(pCol->m_get_f))();
		if (isNull(ret))
		{
			int i = 0;
			std::string::size_type pos = 0;

			while ((pos = sql.find('?', pos)) != std::string::npos)
			{
				if (i == index)
				{
					sql.replace(pos, 1, nullStr);
					break;
				}
				pos += 1;
				i++;
			}
		}
		index --;

		return;
	}

	template<typename Type, typename Entity>
	void ReplaceValue(Entity &entity, i_prepared_statement *pStatement, int &index, _void_def *pColumn, bool insert, ColumnType type, bool withLob)
	{
		column_def<Type, Entity> *pCol = (column_def<Type, Entity> *) pColumn;
		if (pCol->m_columnDef.m_autoincr && insert) return;

		Type ret = (entity.*(pCol->m_get_f))();
		if (isNull(ret)) return;

		if (!withLob)
		{
			if (is_lob<Type>()) return;
		}
		else
		{
			if (is_lob<Type>())
			{
				Type ret = (entity.*(pCol->m_get_f))();
				if (!is_need_update(ret))
					return;
			}
		}

		switch (type)
		{
		case ALL:
			{
				if (pCol->m_columnDef.m_identify && isEmpty(ret))
				{
					//if (SetValueBack(ret, UUID::RandomUUID().ToString()))
					if (SetValueBack(ret, GUIDGenerator::SGetInstance()->NextUUID()))
						(entity.*(pCol->m_set_f))(ret);
				}

				SetValue(pStatement, index, ret);

				index ++;
			}
			break;
		case KEY:
			if (pCol->m_columnDef.m_identify)
			{
				if (isEmpty(ret))
					//if (SetValueBack(ret, UUID::RandomUUID().ToString()))
					if (SetValueBack(ret, GUIDGenerator::SGetInstance()->NextUUID()))
						(entity.*(pCol->m_set_f))(ret);

				SetValue(pStatement, index, ret);

				index ++;
			}
			break;
		case NORMAL:
			if (!pCol->m_columnDef.m_identify)
			{
				SetValue(pStatement, index, ret);
				index ++;
			}
			break;
		}

		return;
	}

	template<typename Entity>
	void UpdateSql(Entity &entity, int index, std::string &sql, int &updateIndex, ColumnType type=ALL, bool withLob=true)
	{
		switch (index)
		{
		case 0:
		{
			UpdateToNull<typename TableDef::t0_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 1:
		{
			UpdateToNull<typename TableDef::t1_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 2:
		{
			UpdateToNull<typename TableDef::t2_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 3:
		{
			UpdateToNull<typename TableDef::t3_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 4:
		{
			UpdateToNull<typename TableDef::t4_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 5:
		{
			UpdateToNull<typename TableDef::t5_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 6:
		{
			UpdateToNull<typename TableDef::t6_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 7:
		{
			UpdateToNull<typename TableDef::t7_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 8:
		{
			UpdateToNull<typename TableDef::t8_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 9:
		{
			UpdateToNull<typename TableDef::t9_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 10:
		{
			UpdateToNull<typename TableDef::t10_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 11:
		{
			UpdateToNull<typename TableDef::t11_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 12:
		{
			UpdateToNull<typename TableDef::t12_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 13:
		{
			UpdateToNull<typename TableDef::t13_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 14:
		{
			UpdateToNull<typename TableDef::t14_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 15:
		{
			UpdateToNull<typename TableDef::t15_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 16:
		{
			UpdateToNull<typename TableDef::t16_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 17:
		{
			UpdateToNull<typename TableDef::t17_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 18:
		{
			UpdateToNull<typename TableDef::t18_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 19:
		{
			UpdateToNull<typename TableDef::t19_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 20:
		{
			UpdateToNull<typename TableDef::t20_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 21:
		{
			UpdateToNull<typename TableDef::t21_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 22:
		{
			UpdateToNull<typename TableDef::t22_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 23:
		{
			UpdateToNull<typename TableDef::t23_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 24:
		{
			UpdateToNull<typename TableDef::t24_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 25:
		{
			UpdateToNull<typename TableDef::t25_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 26:
		{
			UpdateToNull<typename TableDef::t26_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 27:
		{
			UpdateToNull<typename TableDef::t27_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 28:
		{
			UpdateToNull<typename TableDef::t28_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 29:
		{
			UpdateToNull<typename TableDef::t29_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 30:
		{
			UpdateToNull<typename TableDef::t30_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 31:
		{
			UpdateToNull<typename TableDef::t31_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 32:
		{
			UpdateToNull<typename TableDef::t32_type, Entity> (entity, updateIndex, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 33:
		{
			UpdateToNull<typename TableDef::t33_type, Entity> (entity, index, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 34:
		{
			UpdateToNull<typename TableDef::t34_type, Entity> (entity, index, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 35:
		{
			UpdateToNull<typename TableDef::t35_type, Entity> (entity, index, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 36:
		{
			UpdateToNull<typename TableDef::t36_type, Entity> (entity, index, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 37:
		{
			UpdateToNull<typename TableDef::t37_type, Entity> (entity, index, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 38:
		{
			UpdateToNull<typename TableDef::t38_type, Entity> (entity, index, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 39:
		{
			UpdateToNull<typename TableDef::t39_type, Entity> (entity, index, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		case 40:
		{
			UpdateToNull<typename TableDef::t40_type, Entity> (entity, index, m_tableDef.m_columns[index], sql, type, withLob);
			break;
		}
		}
	}

	template<typename Entity>
	void UpdateValue(Entity &entity, i_prepared_statement *pStmt, int index, int &updateIndex, bool insert=false, ColumnType type=ALL, bool withLob=true)
	{
		switch (index)
		{
		case 0:
		{
			ReplaceValue<typename TableDef::t0_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 1:
		{
			ReplaceValue<typename TableDef::t1_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 2:
		{
			ReplaceValue<typename TableDef::t2_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 3:
		{
			ReplaceValue<typename TableDef::t3_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 4:
		{
			ReplaceValue<typename TableDef::t4_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 5:
		{
			ReplaceValue<typename TableDef::t5_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 6:
		{
			ReplaceValue<typename TableDef::t6_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 7:
		{
			ReplaceValue<typename TableDef::t7_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 8:
		{
			ReplaceValue<typename TableDef::t8_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 9:
		{
			ReplaceValue<typename TableDef::t9_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 10:
		{
			ReplaceValue<typename TableDef::t10_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 11:
		{
			ReplaceValue<typename TableDef::t11_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 12:
		{
			ReplaceValue<typename TableDef::t12_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 13:
		{
			ReplaceValue<typename TableDef::t13_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 14:
		{
			ReplaceValue<typename TableDef::t14_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 15:
		{
			ReplaceValue<typename TableDef::t15_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 16:
		{
			ReplaceValue<typename TableDef::t16_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 17:
		{
			ReplaceValue<typename TableDef::t17_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 18:
		{
			ReplaceValue<typename TableDef::t18_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 19:
		{
			ReplaceValue<typename TableDef::t19_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 20:
		{
			ReplaceValue<typename TableDef::t20_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 21:
		{
			ReplaceValue<typename TableDef::t21_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 22:
		{
			ReplaceValue<typename TableDef::t22_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 23:
		{
			ReplaceValue<typename TableDef::t23_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 24:
		{
			ReplaceValue<typename TableDef::t24_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 25:
		{
			ReplaceValue<typename TableDef::t25_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 26:
		{
			ReplaceValue<typename TableDef::t26_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 27:
		{
			ReplaceValue<typename TableDef::t27_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 28:
		{
			ReplaceValue<typename TableDef::t28_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 29:
		{
			ReplaceValue<typename TableDef::t29_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 30:
		{
			ReplaceValue<typename TableDef::t30_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 31:
		{
			ReplaceValue<typename TableDef::t31_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 32:
		{
			ReplaceValue<typename TableDef::t32_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 33:
		{
			ReplaceValue<typename TableDef::t33_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 34:
		{
			ReplaceValue<typename TableDef::t34_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 35:
		{
			ReplaceValue<typename TableDef::t35_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 36:
		{
			ReplaceValue<typename TableDef::t36_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 37:
		{
			ReplaceValue<typename TableDef::t37_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 38:
		{
			ReplaceValue<typename TableDef::t38_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 39:
		{
			ReplaceValue<typename TableDef::t39_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		case 40:
		{
			ReplaceValue<typename TableDef::t40_type, Entity> (entity, pStmt, updateIndex, m_tableDef.m_columns[index], insert, type, withLob);
			break;
		}
		}
	}

	template<typename Type, typename Entity>
	void GetValueToEntity(Entity &entity, i_result_set *pRs, int index, _void_def *pColumn)
	{
		column_def<Type, Entity> *pCol = (column_def<Type, Entity> *) pColumn;

		Type value;
		mix::GetValue(pRs, index, value);

		(entity.*(pCol->m_set_f))(value);

		return;
	}

	template<typename Entity>
	void GetValue(Entity &entity, i_result_set *pRs, int colIndex, int index)
	{
		switch (colIndex)
		{
		case 0:
		{
			GetValueToEntity<typename TableDef::t0_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 1:
		{
			GetValueToEntity<typename TableDef::t1_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 2:
		{
			GetValueToEntity<typename TableDef::t2_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 3:
		{
			GetValueToEntity<typename TableDef::t3_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 4:
		{
			GetValueToEntity<typename TableDef::t4_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 5:
		{
			GetValueToEntity<typename TableDef::t5_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 6:
		{
			GetValueToEntity<typename TableDef::t6_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 7:
		{
			GetValueToEntity<typename TableDef::t7_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 8:
		{
			GetValueToEntity<typename TableDef::t8_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 9:
		{
			GetValueToEntity<typename TableDef::t9_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 10:
		{
			GetValueToEntity<typename TableDef::t10_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 11:
		{
			GetValueToEntity<typename TableDef::t11_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 12:
		{
			GetValueToEntity<typename TableDef::t12_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 13:
		{
			GetValueToEntity<typename TableDef::t13_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 14:
		{
			GetValueToEntity<typename TableDef::t14_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 15:
		{
			GetValueToEntity<typename TableDef::t15_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 16:
		{
			GetValueToEntity<typename TableDef::t16_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 17:
		{
			GetValueToEntity<typename TableDef::t17_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 18:
		{
			GetValueToEntity<typename TableDef::t18_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 19:
		{
			GetValueToEntity<typename TableDef::t19_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 20:
		{
			GetValueToEntity<typename TableDef::t20_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 21:
		{
			GetValueToEntity<typename TableDef::t21_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 22:
		{
			GetValueToEntity<typename TableDef::t22_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 23:
		{
			GetValueToEntity<typename TableDef::t23_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 24:
		{
			GetValueToEntity<typename TableDef::t24_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 25:
		{
			GetValueToEntity<typename TableDef::t25_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 26:
		{
			GetValueToEntity<typename TableDef::t26_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 27:
		{
			GetValueToEntity<typename TableDef::t27_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 28:
		{
			GetValueToEntity<typename TableDef::t28_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 29:
		{
			GetValueToEntity<typename TableDef::t29_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 30:
		{
			GetValueToEntity<typename TableDef::t30_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 31:
		{
			GetValueToEntity<typename TableDef::t31_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 32:
		{
			GetValueToEntity<typename TableDef::t32_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 33:
		{
			GetValueToEntity<typename TableDef::t33_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 34:
		{
			GetValueToEntity<typename TableDef::t34_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 35:
		{
			GetValueToEntity<typename TableDef::t35_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 36:
		{
			GetValueToEntity<typename TableDef::t36_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 37:
		{
			GetValueToEntity<typename TableDef::t37_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 38:
		{
			GetValueToEntity<typename TableDef::t38_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 39:
		{
			GetValueToEntity<typename TableDef::t39_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		case 40:
		{
			GetValueToEntity<typename TableDef::t40_type, Entity> (entity, pRs, index+1, m_tableDef.m_columns[colIndex]);
			break;
		}
		}
	}

	i_connection *GetConnection()
	{
		return transaction_manager::SGetTransactionManager(m_dbname)->GetConnection();
	}

	void TerminateConnection(i_connection *pConn)
	{
		transaction_manager::SGetTransactionManager(m_dbname)->STerminateConnection(pConn);
	}

	void BeginTransaction()
	{
		transaction_manager::SGetTransactionManager(m_dbname)->Begin();
	}
	void CommitTransaction()
	{
		transaction_manager::SGetTransactionManager(m_dbname)->Commit();
	}
	void RollbackTransaction()
	{
		transaction_manager::SGetTransactionManager(m_dbname)->Rollback();
	}

	InsertSQL_Fun GetInsertSQLFunction()
	{
		i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
		if (pCreater != NULL)
		{
			return pCreater->GetInsertSQLFunction();
		}
		else
		{
			throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
		}
	}

	UpdateSQL_Fun GetUpdateSQLFunction()
	{
		i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
		if (pCreater != NULL)
		{
			return pCreater->GetUpdateSQLFunction();
		}
		else
		{
			throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
		}
	}

	FindSQL_Fun GetFindSQLFunction()
	{
		i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
		if (pCreater != NULL)
		{
			return pCreater->GetFindSQLFunction();
		}
		else
		{
			throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
		}
	}

	DumySQL_Fun GetDumySQLFunction()
	{
		i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
		if (pCreater != NULL)
		{
			return pCreater->GetDumySQLFunction();
		}
		else
		{
			throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
		}
	}

	FindLobForUpdateSQL_Fun GetFindLobForUpdateSQLFunction()
	{
		i_creater *pCreater = database_factory::SGetInstance()->GetCreater(m_dbname);
		if (pCreater != NULL)
		{
			return pCreater->GetFindLobForUpdateSQLFunction();
		}
		else
		{
			throw sql_exception(DATABASE_NO_CREATER_NO, "No database creater!");
		}
	}

	template<typename Type, typename Entity>
	bool IsColumnNeedUpdate(Entity &entity, int index, _void_def *pColumn)
	{
		column_def<Type, Entity> *pCol = (column_def<Type, Entity> *) pColumn;

		Type t = (entity.*(pCol->m_get_f))();

		return is_need_update(t);
	}

	template<typename Entity>
	bool IsNeedUpdate(Entity &entity)
	{
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			switch(i)
			{
			case 0:
			{
				if (IsColumnNeedUpdate<typename TableDef::t0_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 1:
			{
				if (IsColumnNeedUpdate<typename TableDef::t1_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 2:
			{
				if (IsColumnNeedUpdate<typename TableDef::t2_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 3:
			{
				if (IsColumnNeedUpdate<typename TableDef::t3_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 4:
			{
				if (IsColumnNeedUpdate<typename TableDef::t4_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 5:
			{
				if (IsColumnNeedUpdate<typename TableDef::t5_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 6:
			{
				if (IsColumnNeedUpdate<typename TableDef::t6_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 7:
			{
				if (IsColumnNeedUpdate<typename TableDef::t7_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 8:
			{
				if (IsColumnNeedUpdate<typename TableDef::t8_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 9:
			{
				if (IsColumnNeedUpdate<typename TableDef::t9_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 10:
			{
				if (IsColumnNeedUpdate<typename TableDef::t10_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 11:
			{
				if (IsColumnNeedUpdate<typename TableDef::t11_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 12:
			{
				if (IsColumnNeedUpdate<typename TableDef::t12_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 13:
			{
				if (IsColumnNeedUpdate<typename TableDef::t13_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 14:
			{
				if (IsColumnNeedUpdate<typename TableDef::t14_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 15:
			{
				if (IsColumnNeedUpdate<typename TableDef::t15_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 16:
			{
				if (IsColumnNeedUpdate<typename TableDef::t16_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 17:
			{
				if (IsColumnNeedUpdate<typename TableDef::t17_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 18:
			{
				if (IsColumnNeedUpdate<typename TableDef::t18_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 19:
			{
				if (IsColumnNeedUpdate<typename TableDef::t19_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 20:
			{
				if (IsColumnNeedUpdate<typename TableDef::t20_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 21:
			{
				if (IsColumnNeedUpdate<typename TableDef::t21_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 22:
			{
				if (IsColumnNeedUpdate<typename TableDef::t22_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 23:
			{
				if (IsColumnNeedUpdate<typename TableDef::t23_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 24:
			{
				if (IsColumnNeedUpdate<typename TableDef::t24_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 25:
			{
				if (IsColumnNeedUpdate<typename TableDef::t25_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 26:
			{
				if (IsColumnNeedUpdate<typename TableDef::t26_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 27:
			{
				if (IsColumnNeedUpdate<typename TableDef::t27_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 28:
			{
				if (IsColumnNeedUpdate<typename TableDef::t28_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 29:
			{
				if (IsColumnNeedUpdate<typename TableDef::t29_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 30:
			{
				if (IsColumnNeedUpdate<typename TableDef::t30_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 31:
			{
				if (IsColumnNeedUpdate<typename TableDef::t31_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 32:
			{
				if (IsColumnNeedUpdate<typename TableDef::t32_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 33:
			{
				if (IsColumnNeedUpdate<typename TableDef::t33_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 34:
			{
				if (IsColumnNeedUpdate<typename TableDef::t34_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 35:
			{
				if (IsColumnNeedUpdate<typename TableDef::t35_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 36:
			{
				if (IsColumnNeedUpdate<typename TableDef::t36_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 37:
			{
				if (IsColumnNeedUpdate<typename TableDef::t37_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 38:
			{
				if (IsColumnNeedUpdate<typename TableDef::t38_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 39:
			{
				if (IsColumnNeedUpdate<typename TableDef::t39_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			case 40:
			{
				if (IsColumnNeedUpdate<typename TableDef::t40_type, Entity>(entity, i, m_tableDef.m_columns[i]))
					return true;
				break;
			}
			}
		}
		return false;
	}

	template<typename Lob, typename Entity>
	void UpdateLobColumn(Entity &entity, unsigned int &index, _void_def *pColumn, i_prepared_statement *pStmt)
	{
		column_def<Lob, Entity> *pCol = (column_def<Lob, Entity> *) pColumn;

		Lob lob = (entity.*(pCol->m_get_f))();
		if (is_need_update(lob))
		{
			SetValue(pStmt, ++index, lob);
		}
	}

	template<typename Entity>
	void UpdateLobColumns(Entity &entity, i_prepared_statement *pStmt)
	{
		unsigned int indexLob = 0;
		for (unsigned int i = 0; i < (unsigned int)m_tableDef.m_colNum; i++)
		{
			switch(i)
			{
			case 0:
			{
				UpdateLobColumn<typename TableDef::t0_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 1:
			{
				UpdateLobColumn<typename TableDef::t1_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 2:
			{
				UpdateLobColumn<typename TableDef::t2_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 3:
			{
				UpdateLobColumn<typename TableDef::t3_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 4:
			{
				UpdateLobColumn<typename TableDef::t4_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 5:
			{
				UpdateLobColumn<typename TableDef::t5_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 6:
			{
				UpdateLobColumn<typename TableDef::t6_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 7:
			{
				UpdateLobColumn<typename TableDef::t7_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 8:
			{
				UpdateLobColumn<typename TableDef::t8_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 9:
			{
				UpdateLobColumn<typename TableDef::t9_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 10:
			{
				UpdateLobColumn<typename TableDef::t10_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 11:
			{
				UpdateLobColumn<typename TableDef::t11_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 12:
			{
				UpdateLobColumn<typename TableDef::t12_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 13:
			{
				UpdateLobColumn<typename TableDef::t13_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 14:
			{
				UpdateLobColumn<typename TableDef::t14_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 15:
			{
				UpdateLobColumn<typename TableDef::t15_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 16:
			{
				UpdateLobColumn<typename TableDef::t16_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 17:
			{
				UpdateLobColumn<typename TableDef::t17_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 18:
			{
				UpdateLobColumn<typename TableDef::t18_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 19:
			{
				UpdateLobColumn<typename TableDef::t19_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 20:
			{
				UpdateLobColumn<typename TableDef::t20_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 21:
			{
				UpdateLobColumn<typename TableDef::t21_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 22:
			{
				UpdateLobColumn<typename TableDef::t22_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 23:
			{
				UpdateLobColumn<typename TableDef::t23_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 24:
			{
				UpdateLobColumn<typename TableDef::t24_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 25:
			{
				UpdateLobColumn<typename TableDef::t25_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 26:
			{
				UpdateLobColumn<typename TableDef::t26_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 27:
			{
				UpdateLobColumn<typename TableDef::t27_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 28:
			{
				UpdateLobColumn<typename TableDef::t28_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 29:
			{
				UpdateLobColumn<typename TableDef::t29_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 30:
			{
				UpdateLobColumn<typename TableDef::t30_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 31:
			{
				UpdateLobColumn<typename TableDef::t31_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 32:
			{
				UpdateLobColumn<typename TableDef::t32_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 33:
			{
				UpdateLobColumn<typename TableDef::t33_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 34:
			{
				UpdateLobColumn<typename TableDef::t34_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 35:
			{
				UpdateLobColumn<typename TableDef::t35_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 36:
			{
				UpdateLobColumn<typename TableDef::t36_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 37:
			{
				UpdateLobColumn<typename TableDef::t37_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 38:
			{
				UpdateLobColumn<typename TableDef::t38_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 39:
			{
				UpdateLobColumn<typename TableDef::t39_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			case 40:
			{
				UpdateLobColumn<typename TableDef::t40_type, Entity>(entity, indexLob, m_tableDef.m_columns[i], pStmt);
				break;
			}
			}
		}
	}

public:
	Dao(TableDef &tblDef, std::string dbname = "") :
		PersistDao(dbname), m_tableDef(tblDef)
	{

	}

	template<typename Entity>
	int Insert(Entity &entity)
	{
		// 产生SQL语句
		int nRet = 0;
		std::string message;
		int errcode = 0;

		std::string sql1;

		sql1.append("insert into ");
		sql1.append(m_tableDef.m_tableName);
		sql1.append(" (");

		std::string sql2;
		sql2.append(" values (");

		std::string sql3;
		std::string sql4;

		sql_def sql_def(&sql1, &sql2, &sql3, &sql4);

		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(&entity, &sql_def, i, GetInsertSQLFunction(), COLUMN_ALL, false);
		}

		sql1.erase(sql1.size()-2, 2);
		sql1.append(")");

		sql2.erase(sql2.size()-2, 2);
		sql2.append(")");

		i_connection *pConn = NULL;
		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			std::string sql = sql1 + sql2 + sql3 + sql4;

			int updateIndex = m_tableDef.m_colNum - 1;
			for (int i = m_tableDef.m_colNum - 1; i >= 0; i--)
			{
				UpdateSql(entity, i, sql, updateIndex, ALL, true);
			}

			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql));

			updateIndex = 1;
			for (int i = 0; i < m_tableDef.m_colNum; i++)
			{
				UpdateValue(entity, pStmt.Value(), i, updateIndex, true, ALL, true);
			}

			if (pStmt->NeedUpdateBlob() && IsNeedUpdate(entity))
			{
				BeginTransaction();
				nRet = pStmt->ExecuteUpdate();
				pStmt->Close();

				UpdateLob(entity, pConn);
				CommitTransaction();
			}
			else
			{
				nRet = pStmt->ExecuteUpdate();
				pStmt->Close();
			}

			TerminateConnection(pConn);

		}
		catch (sql_exception &e)
		{
			RollbackTransaction();
			if (pConn != NULL)
				TerminateConnection(pConn);

			errcode = e.GetErrNo();
			message.append(e.what());
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());

		return nRet;
	}

	template<typename Entity>
	int Update(Entity entity)
	{
		int nRet = 0;
		std::string message;
		int errcode = 0;

		std::string sql1;
		sql1.append("update ");
		sql1.append(m_tableDef.m_tableName);
		sql1.append(" set ");

		std::string sql2;
		sql2.append(" where ");

		std::string sql3;
		std::string sql4;

		sql_def sql_def(&sql1, &sql2, &sql3, &sql4);
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(&entity, &sql_def, i, GetUpdateSQLFunction(), COLUMN_ALL, false);
		}

		sql1.erase(sql1.size()-2, 2);
		sql2.erase(sql2.size()-4, 4);

		i_connection *pConn = NULL;
		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			std::string sql = sql1 + sql2 + sql3 + sql4;

			int updateIndex = m_tableDef.m_colNum - 1;
			for (int i = m_tableDef.m_colNum - 1; i >= 0; i--)
			{
				UpdateSql(entity, i, sql, updateIndex, KEY, false);
			}
			for (int i = m_tableDef.m_colNum - 1; i >= 0; i--)
			{
				UpdateSql(entity, i, sql, updateIndex, NORMAL, true);
			}

			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql));

			updateIndex = 1;
			for (int i = 0; i < m_tableDef.m_colNum; i++)
			{
				UpdateValue(entity, pStmt.Value(), i, updateIndex, false, NORMAL, true);
			}
			for (int i = 0; i < m_tableDef.m_colNum; i++)
			{
				UpdateValue(entity, pStmt.Value(), i, updateIndex, false, KEY, true);
			}

			if (pStmt->NeedUpdateBlob() && IsNeedUpdate(entity))
			{
				BeginTransaction();
				nRet = pStmt->ExecuteUpdate();
				pStmt->Close();

				UpdateLob(entity, pConn);
				CommitTransaction();
			}
			else
			{
				nRet = pStmt->ExecuteUpdate();
				pStmt->Close();
			}

			TerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			RollbackTransaction();
			if (pConn != NULL)
				TerminateConnection(pConn);

			errcode = e.GetErrNo();
			message.append(e.what());
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());

		return nRet;
	}

	template<typename Entity, typename... _Args>
	int UpdateByCondition(Entity entity, std::string cond, _Args... args)
	{
		int nRet = 0;
		std::string message;
		int errcode = 0;

		std::string sql1;
		sql1.append("update ");
		sql1.append(m_tableDef.m_tableName);
		sql1.append(" set ");

		std::string sql2;
		sql2.append(" where ");
		sql2.append(cond);

		sql_def sql_def(&sql1, &sql2);
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(&entity, &sql_def, i, GetUpdateSQLFunction(), COLUMN_ALL, false);
		}

		sql1.erase(sql1.size()-2, 2);
		sql2.erase(sql2.size()-4, 4);

		i_connection *pConn = NULL;
		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			std::string sql = sql1 + sql2;

			int updateIndex = m_tableDef.m_colNum - 1;
			for (int i = m_tableDef.m_colNum - 1; i >= 0; i--)
			{
				UpdateSql(entity, i, sql, updateIndex, KEY, false);
			}
			for (int i = m_tableDef.m_colNum - 1; i >= 0; i--)
			{
				UpdateSql(entity, i, sql, updateIndex, NORMAL, true);
			}

			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql));

			updateIndex = 1;
			for (int i = 0; i < m_tableDef.m_colNum; i++)
			{
				UpdateValue(entity, pStmt.Value(), i, updateIndex, false, NORMAL, true);
			}
			for (int i = 0; i < m_tableDef.m_colNum; i++)
			{
				UpdateValue(entity, pStmt.Value(), i, updateIndex, false, KEY, true);
			}

			nRet = pStmt->ExecuteUpdate();
			pStmt->Close();

			if (pStmt->NeedUpdateBlob() && IsNeedUpdate(entity))
			{
				BeginTransaction();
				UpdateLob(entity, pConn);
				CommitTransaction();
			}

			TerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			RollbackTransaction();
			if (pConn != NULL)
				TerminateConnection(pConn);

			errcode = e.GetErrNo();
			message.append(e.what());
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());

		return nRet;
	}

	template<typename Entity>
	int UpdateWithoutLob(Entity entity)
	{
		int nRet;
		std::string message;
		int errcode = 0;

		std::string sql1;
		sql1.append("update ");
		sql1.append(m_tableDef.m_tableName);
		sql1.append(" set ");

		std::string sql2;
		sql2.append(" where ");

		sql_def sql_def(&sql1, &sql2);
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(&entity, &sql_def, i, GetUpdateSQLFunction(), COLUMN_NORM, false);
		}

		sql1.erase(sql1.size()-2, 2);
		sql2.erase(sql2.size()-4, 4);

		i_connection *pConn = NULL;
		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			std::string sql = sql1 + sql2;

			int updateIndex = m_tableDef.m_colNum - 1;
			for (int i = m_tableDef.m_colNum - 1; i >= 0; i--)
			{
				UpdateSql(entity, i, sql, updateIndex, KEY, false);
			}
			for (int i = m_tableDef.m_colNum - 1; i >= 0; i--)
			{
				UpdateSql(entity, i, sql, updateIndex, NORMAL, false);
			}

			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql));

			updateIndex = 1;
			for (int i = 0; i < m_tableDef.m_colNum; i++)
			{
				UpdateValue(entity, pStmt.Value(), i, updateIndex, false, NORMAL, false);
			}
			for (int i = 0; i < m_tableDef.m_colNum; i++)
			{
				UpdateValue(entity, pStmt.Value(), i, updateIndex, false, KEY, false);
			}

			nRet = pStmt->ExecuteUpdate();
			pStmt->Close();

			if (pStmt->NeedUpdateBlob() && IsNeedUpdate(entity))
			{
				UpdateLob(entity, pConn);
			}

			TerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());

		return nRet;
	}

	template<typename Entity>
	int UpdateLob(Entity &entity)
	{
		int nRet = 0;
		std::string message;
		int errcode = 0;

		i_connection *pConn = NULL;
		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			nRet = UpdateLob(entity, pConn);
			TerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());

		return nRet;
	}

	template<typename Entity>
	int UpdateLob(Entity &entity, i_connection *pConn)
	{
		int nRet = 0;
		std::string sql1;
		sql1.append("select ");

		std::string sql2;
		sql2.append(" from ");
		sql2.append(m_tableDef.m_tableName);
		sql2.append(" where ");

		sql_def sql_def(&sql1, &sql2);
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(&entity, &sql_def, i, GetFindLobForUpdateSQLFunction(), COLUMN_LOB, false);
		}

		sql1.erase(sql1.size()-2, 2);
		sql2.erase(sql2.size()-4, 4);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql1+sql2 + " for update"));

			int updateIndex = 1;
			for (int i = 0; i < m_tableDef.m_colNum; i++)
			{
				UpdateValue(entity, pStmt.Value(), i, updateIndex, false, KEY, true);
			}

			UpdateLobColumns(entity, pStmt.Value());

			nRet = pStmt->ExecuteUpdate();

			pStmt->Close();

			return nRet;
		}
		catch (sql_exception &e)
		{
			throw e;
		}
	}

	template<typename Entity>
	int GetEntityByKey(Entity &entity)
	{
		int nRet = 0;

		int errcode = 0;
		std::string message;

		std::string sql1;
		sql1.append("select ");

		std::string sql2;
		sql2.append(" from ");
		sql2.append(m_tableDef.m_tableName);
		sql2.append(" where ");

		sql_def sql_def(&sql1, &sql2);
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(&entity, &sql_def, i, GetFindSQLFunction(), COLUMN_ALL, true);
		}

		sql1.erase(sql1.size()-2, 2);
		sql2.erase(sql2.size()-4, 4);

		i_connection *pConn = NULL;

		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(e.GetErrNo(), message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql1+sql2));

			int updateIndex = 1;
			for (int i = 0; i < m_tableDef.m_colNum; i++)
			{
				UpdateValue(entity, pStmt.Value(), i, updateIndex, false, KEY, false);
			}

			any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

			if (pRs->Next())
			{
				for (int i = 0; i < m_tableDef.m_colNum; i++)
				{
					GetValue(entity, pRs.Value(), i, i);
				}
				nRet ++;
			}

			pRs->Close();
			pStmt->Close();
			TerminateConnection(pConn);
			pConn = NULL;
		}
		catch (sql_exception &e)
		{
			errcode = e.GetErrNo();
			if (pConn != NULL)
				TerminateConnection(pConn);
			message.append(e.what());
			errcode = e.GetErrNo();
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());

		return nRet;
	}

	template<typename Entity, typename... _Args>
	int GetEntityByCondition(Entity &entity, std::string cond, _Args... args)
	{
		int nRet = 0;
		std::string message;
		int errcode = 0;

		std::string sql1;
		sql1.append("select ");

		std::string sql2;
		sql2.append(" from ");
		sql2.append(m_tableDef.m_tableName);
		sql2.append(" where ");
		sql2.append(cond);

		sql_def sql_def(&sql1, &sql2);
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(&entity, &sql_def, i, GetDumySQLFunction(), COLUMN_ALL, true);
		}

		sql1.erase(sql1.size()-2, 2);

		i_connection *pConn = NULL;

		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(e.GetErrNo(), message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql1+sql2));

    		int nIndex = 1;
    		SetStatementValue(pStmt.Value(), nIndex, args...);

    		any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

			if (pRs->Next())
			{
				for (int i = 0; i < m_tableDef.m_colNum; i++)
				{
					GetValue(entity, pRs.Value(), i, i);
				}
				nRet ++;
			}

			pRs->Close();
			pStmt->Close();
			TerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);
			message.append(e.what());
			errcode = e.GetErrNo();
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());

		return nRet;
	}

	template<typename Entity, typename... _Args>
	void SearchEntityByCondition(std::string cond, std::vector<Entity *> &result, bool withLob, int first, int size, _Args... args)
	{
		std::string message;
		int errcode = 0;

		std::string sql1;
		sql1.append("select ");

		std::string sql2;
		sql2.append(" from ");
		sql2.append(m_tableDef.m_tableName);
		sql2.append(" where ");
		sql2.append(cond);

		sql_def sql_def(&sql1, &sql2);
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(NULL, &sql_def, i, GetDumySQLFunction(), withLob?COLUMN_ALL:COLUMN_NORM, true);
		}

		sql1.erase(sql1.size()-2, 2);

		i_connection *pConn = NULL;

		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql1+sql2));

			int nIndex = 1;
    		SetStatementValue(pStmt.Value(), nIndex, args...);

    		any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

			int nPos = 0;
			while (pRs->Next())
			{
				if (nPos >= first && (size <= 0 || nPos < first + size))
				{
					Entity *pEntity = new Entity;
					int k = 0;
					for (int i = 0; i < m_tableDef.m_colNum; i++)
					{
						if (!withLob)
						{
							if (is_lob<TableDef>(i))
								continue;
						}
						GetValue(*pEntity, pRs.Value(), i, k++);
					}
					result.push_back(pEntity);
				}
				nPos ++;
			}

			pRs->Close();
			pStmt->Close();
			TerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);
			message.append(e.what());
			errcode = e.GetErrNo();
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());
	}

	template<typename Entity>
	void SearchEntityByCondition(std::string cond, std::vector<Entity *> &result, std::vector<AnyType> &param, bool withLob, int first, int size)
	{
		std::string message;
		int errcode = 0;

		std::string sql1;
		sql1.append("select ");

		std::string sql2;
		sql2.append(" from ");
		sql2.append(m_tableDef.m_tableName);
		sql2.append(" where ");
		sql2.append(cond);

		sql_def sql_def(&sql1, &sql2);
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(NULL, &sql_def, i, GetDumySQLFunction(), withLob?COLUMN_ALL:COLUMN_NORM, true);
		}

		sql1.erase(sql1.size()-2, 2);

		i_connection *pConn = NULL;

		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql1+sql2));

			unsigned int nIndex = 1;
			for (unsigned int i = 0; i < param.size(); i++)
			{
				AnyType &pm = param[i];
				switch (pm.GetType())
				{
				case AnyType::INT:
					SetValue<int>(pStmt.Value(), nIndex++, pm.GetInt());
					break;
				case AnyType::CHAR:
					SetValue(pStmt.Value(), nIndex++, pm.GetChar());
					break;
				case AnyType::SHORT:
					SetValue(pStmt.Value(), nIndex++, pm.GetShort());
					break;
				case AnyType::LONG:
					SetValue(pStmt.Value(), nIndex++, pm.GetLong());
					break;
				case AnyType::DOUBLE:
					SetValue(pStmt.Value(), nIndex++, pm.GetDouble());
					break;
				case AnyType::FLOAT:
					SetValue(pStmt.Value(), nIndex++, pm.GetFloat());
					break;
				case AnyType::STRING:
					SetValue(pStmt.Value(), nIndex++, pm.GetString());
					break;
				case AnyType::DATE:
					SetValue(pStmt.Value(), nIndex++, pm.GetDate());
					break;
				case AnyType::TIMESTAMP:
					SetValue(pStmt.Value(), nIndex++, pm.GetTimestamp());
					break;
				default:
					break;
				}
			}

    		any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

			int nPos = 0;
			while (pRs->Next())
			{
				if (nPos >= first && (size <= 0 || nPos < first + size))
				{
					Entity *pEntity = new Entity;
					int k = 0;
					for (int i = 0; i < m_tableDef.m_colNum; i++)
					{
						if (!withLob)
						{
							if (is_lob<TableDef>(i))
								continue;
						}
						GetValue(*pEntity, pRs.Value(), i, k++);
					}
					result.push_back(pEntity);
				}
				nPos ++;
			}

			pRs->Close();
			pStmt->Close();
			TerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);
			message.append(e.what());
			errcode = e.GetErrNo();
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());
	}

	template<typename Entity, typename... _Args>
	void SearchEntityByCondition(std::string cond, i_search_process *pDataProcess, bool withLob, int first, int size, _Args... args)
	{
		std::string message;
		int errcode = 0;

		std::string sql1;
		sql1.append("select ");

		std::string sql2;
		sql2.append(" from ");
		sql2.append(m_tableDef.m_tableName);
		sql2.append(" where ");
		sql2.append(cond);

		sql_def sql_def(&sql1, &sql2);
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(NULL, &sql_def, i, GetDumySQLFunction(), withLob?COLUMN_ALL:COLUMN_NORM, true);
		}

		sql1.erase(sql1.size()-2, 2);

		i_connection *pConn = NULL;

		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql1+sql2));

			int nIndex = 1;
    		SetStatementValue(pStmt.Value(), nIndex, args...);

    		any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

			int nPos = 0;
			while (pRs->Next())
			{
				if (nPos >= first && (size <= 0 || nPos < first + size))
				{
					Entity *pEntity = new Entity;
					int k = 0;
					for (int i = 0; i < m_tableDef.m_colNum; i++)
					{
						if (!withLob)
						{
							if (is_lob<TableDef>(i))
								continue;
						}
						GetValue(*pEntity, pRs.Value(), i, k++);
					}
					if (pDataProcess->IsCanceled())
						break;
					pDataProcess->Process(pEntity);
				}
				nPos ++;
			}

			pRs->Close();
			pStmt->Close();
			TerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);
			message.append(e.what());
			errcode = e.GetErrNo();
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());
	}

	template<typename Entity, typename... _Args>
	void SearchEntityByCondition(std::string cond, i_search_process *pDataProcess, std::vector<AnyType> &param, bool withLob, int first, int size)
	{
		std::string message;
		int errcode = 0;

		std::string sql1;
		sql1.append("select ");

		std::string sql2;
		sql2.append(" from ");
		sql2.append(m_tableDef.m_tableName);
		sql2.append(" where ");
		sql2.append(cond);

		sql_def sql_def(&sql1, &sql2);
		for (int i = 0; i < m_tableDef.m_colNum; i++)
		{
			CommonCall<Entity>(NULL, &sql_def, i, GetDumySQLFunction(), withLob?COLUMN_ALL:COLUMN_NORM, true);
		}

		sql1.erase(sql1.size()-2, 2);

		i_connection *pConn = NULL;

		try
		{
			pConn = GetConnection();
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);

			message.append(e.what());
			errcode = e.GetErrNo();
			throw sql_exception(errcode, message.c_str());
		}

		//pthread_cleanup_push(transaction_manager::Cleanup, pConn);

		try
		{
			any_ptr<i_prepared_statement> pStmt(pConn->PrepareStatement(sql1+sql2));

			unsigned int nIndex = 1;
			for (unsigned int i = 0; i < param.size(); i++)
			{
				AnyType &pm = param[i];
				switch (pm.GetType())
				{
				case AnyType::INT:
					SetValue<int>(pStmt.Value(), nIndex++, pm.GetInt());
					break;
				case AnyType::CHAR:
					SetValue(pStmt.Value(), nIndex++, pm.GetChar());
					break;
				case AnyType::SHORT:
					SetValue(pStmt.Value(), nIndex++, pm.GetShort());
					break;
				case AnyType::LONG:
					SetValue(pStmt.Value(), nIndex++, pm.GetLong());
					break;
				case AnyType::DOUBLE:
					SetValue(pStmt.Value(), nIndex++, pm.GetDouble());
					break;
				case AnyType::FLOAT:
					SetValue(pStmt.Value(), nIndex++, pm.GetFloat());
					break;
				case AnyType::STRING:
					SetValue(pStmt.Value(), nIndex++, pm.GetString());
					break;
				case AnyType::DATE:
					SetValue(pStmt.Value(), nIndex++, pm.GetDate());
					break;
				case AnyType::TIMESTAMP:
					SetValue(pStmt.Value(), nIndex++, pm.GetTimestamp());
					break;
				default:
					break;
				}
			}

    		any_ptr<i_result_set> pRs(pStmt->ExecuteQuery());

			int nPos = 0;
			while (pRs->Next())
			{
				if (nPos >= first && (size <= 0 || nPos < first + size))
				{
					Entity *pEntity = new Entity;
					int k = 0;
					for (int i = 0; i < m_tableDef.m_colNum; i++)
					{
						if (!withLob)
						{
							if (is_lob<TableDef>(i))
								continue;
						}
						GetValue(*pEntity, pRs.Value(), i, k++);
					}
					if (pDataProcess->IsCanceled())
						break;
					pDataProcess->Process(pEntity);
				}
				nPos ++;
			}

			pRs->Close();
			pStmt->Close();
			TerminateConnection(pConn);
		}
		catch (sql_exception &e)
		{
			if (pConn != NULL)
				TerminateConnection(pConn);
			message.append(e.what());
			errcode = e.GetErrNo();
		}

		//pthread_cleanup_pop(0);

		if (!message.empty())
			throw sql_exception(errcode, message.c_str());
	}
};

}
#endif /* HIBERNATE_HPP_ */
