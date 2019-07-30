/*
 * dbmapping.h
 *
 *  Created on: 2018-4-25
 *      Author: xiaoba-8
 */

#ifndef DBMAPPING_H_
#define DBMAPPING_H_


#include <string>
namespace mix
{

struct _void_def
{
};


struct sql_def : _void_def
{
	std::string *m_pSql1;
	std::string *m_pSql2;
	std::string *m_pSql3;
	std::string *m_pSql4;
	sql_def() {}
	sql_def(std::string *p1, std::string *p2, std::string *p3 = NULL, std::string *p4 = NULL) : m_pSql1(p1), m_pSql2(p2), m_pSql3(p3), m_pSql4(p4) {}
};


struct ColumnDef;

typedef void (*InsertSQL_Fun)(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql);

typedef void (*UpdateSQL_Fun)(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql);

typedef void (*FindSQL_Fun)(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql);

typedef void (*DumySQL_Fun)(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql);

typedef void (*FindLobForUpdateSQL_Fun)(ColumnDef &colDef, int index, bool is_lob, std::string tbl, _void_def *pSql);


struct ColumnDef
{
	std::string m_columnName;
	bool m_identify;
	bool m_autoincr;
	ColumnDef() {}
	ColumnDef(const char *columnName, bool isKey = false,	bool autoincr = false) :
		m_columnName(columnName),
				m_identify(isKey), m_autoincr(autoincr)
	{}
	ColumnDef(std::string columnName, bool isKey = false,	bool autoincr = false) :
		m_columnName(columnName),
				m_identify(isKey), m_autoincr(autoincr)
	{}
};

}

#endif /* DBMAPPING_H_ */
