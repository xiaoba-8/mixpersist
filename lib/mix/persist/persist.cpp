/*
 * persist.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: xiaoba-8
 */

#include <mix/persist/persist.hpp>


namespace mix
{

PersistDao::PersistDao(std::string dbname) : m_dbname(dbname)
{

}

PersistDao::~PersistDao()
{

}

std::vector<std::vector<mix::AnyType> > PersistDao::Search(std::string sql, int first, int size)
{
	mix::i_connection *pConn = NULL;

	try
	{
		pConn = mix::transaction_manager::SGetTransactionManager()->GetConnection();
		mix::any_ptr<mix::i_prepared_statement> pStmt(pConn->PrepareStatement(sql));
		mix::any_ptr<mix::i_result_set> pRs(pStmt->ExecuteQuery());

		std::vector<std::vector<mix::AnyType> > result;
		int nCount = pRs->GetColumnCount();
		int nPos = 0;
		while (pRs->Next())
		{
			if (nPos >= first && (size <= 0 || nPos < first + size))
			{
				std::vector<mix::AnyType> row;

				for (int i=0; i < nCount; i++)
				{
					mix::AnyType val = pRs->GetObject(i+1);
					row.push_back(val);
				}
				result.push_back(row);
			}
			nPos ++;
		}

		pRs->Close();
		pStmt->Close();

		mix::transaction_manager::SGetTransactionManager()->STerminateConnection(pConn);

		return result;
	}
	catch (mix::sql_exception &e)
	{
		if (pConn != NULL)
			mix::transaction_manager::SGetTransactionManager()->STerminateConnection(pConn);

		std::string message = "PersistDao::Search :" + sql;
		message.append(e.what());
		throw mix::sql_exception(e.GetErrNo(), message.c_str());
	}
}


void PersistDao::SetStatementValue(mix::i_prepared_statement *pStmt, int &index)
{
}

void PersistDao::SetDbname(std::string dbname)
{
	m_dbname = dbname;
}

std::string PersistDao::GetDbName()
{
	return m_dbname;
}

template<>
bool is_need_update(mix::Blob &blob)
{
	return blob.IsNeedUpdate();
}

template<>
bool is_need_update(mix::Clob &clob)
{
	return clob.IsNeedUpdate();
}

template<>
bool is_lob<Blob>()
{
	return true;
}

template<>
bool is_lob<Clob>()
{

	return true;
}

template <>
bool isEmpty<std::string>(std::string t)
{
	if (t.size() == 0)
		return true;
	else
		return false;
}

template <>
bool isNull<mix::Integer>(mix::Integer t)
{
	return t.IsNull();
}

template <>	/*
 * 根据条件查找数据，返回符合条件的数据
 *    参数：
 *     cond     查询条件，SQL语句中where之后的部分
 *     result   返回的记录集
 *     first  返回结果集的起始索引
 *     size   返回结果集的最大容量
 *    返回值：
 *      当查询到数据时，返回1，否则返回0
 */

bool isNull<mix::UInteger>(mix::UInteger t)
{
	return t.IsNull();
}

template <>
bool isNull<mix::Long>(mix::Long t)
{
	return t.IsNull();
}

template <>
bool isNull<mix::Float>(mix::Float t)
{
	return t.IsNull();
}

template <>
bool isNull<mix::Double>(mix::Double t)
{
	return t.IsNull();
}


template <>
bool SetValueBack<std::string>(std::string &t, std::string v)
{
	t = v;
	return true;
}

}
