/*
 * dbdatas.cpp
 *
 *  Created on: Mar 24, 2018
 *      Author: xiaoba-8
 */

#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <mix/database/dbdatas.h>
#include "time-tzset.h"

namespace mix
{

namespace dbd
{
void ReplaceNumberToString(std::string &fmt, std::string token, int num, int w)
{
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(w) << num;
	ss.flush();

	if (fmt.find(token) != std::string::npos)
		fmt.replace(fmt.find(token), token.size(), ss.str());
}
}

Date::Date() :
	m_isNull(false)
{
	time(&m_time);
}

Date::Date(time_t t) :
	m_isNull(false)
{
	m_time = t;
}

Date::Date(const Date &a)
{
	m_time = a.m_time;
	m_isNull = a.m_isNull;
}

Date::Date(int year, unsigned int month, unsigned int day, unsigned int hour,
		unsigned int minute, unsigned int seconds) :
	m_isNull(false)
{
	SetDate(year, month, day, hour, minute, seconds);
}

Date::~Date()
{

}

void Date::SetDate(int year, unsigned int month, unsigned int day,
		unsigned int hour, unsigned int minute, unsigned int seconds)
{
	struct tm t;

	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	t.tm_mday = day;
	t.tm_hour = hour + persist_get_local_timezone()/3600;
	t.tm_min = minute;
	t.tm_sec = seconds;
	t.tm_isdst = 0;

	m_time = mktime(&t);

	m_isNull = false;
}

void Date::SetLocalDate(int year, unsigned int month, unsigned int day,
		unsigned int hour, unsigned int minute, unsigned int seconds)
{
	struct tm t;

	tzset();
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	t.tm_mday = day;
	t.tm_hour = hour + persist_get_local_timezone() / 3600;
	t.tm_min = minute;
	t.tm_sec = seconds;
	t.tm_isdst = 0;

	m_time = mktime(&t);

	m_isNull = false;
}

void Date::GetDate(int &year, unsigned int &month, unsigned int &day,
		unsigned int &hour, unsigned int &min, unsigned int &sec) const
{
	struct tm ltr;
	//struct tm *ptr = gmtime_r(&m_time, &ltr);
	struct tm *ptr = persist_my_gmtime_r(&m_time, &ltr);

	year = ptr->tm_year + 1900;
	month = ptr->tm_mon + 1;
	day = ptr->tm_mday;
	hour = ptr->tm_hour;
	min = ptr->tm_min;
	sec = ptr->tm_sec;
}

void Date::GetLocalDate(int &year, unsigned int &month, unsigned int &day,
		unsigned int &hour, unsigned int &min, unsigned int &sec) const
{
	struct tm ltr;
	//struct tm *ptr = localtime_r(&m_time, &ltr);
	struct tm *ptr = persist_my_localtime_r(&m_time, -persist_get_local_timezone(), &ltr);

	year = ptr->tm_year + 1900;
	month = ptr->tm_mon + 1;
	day = ptr->tm_mday;
	hour = ptr->tm_hour;
	min = ptr->tm_min;
	sec = ptr->tm_sec;
}

std::string Date::ToText(const std::string &fmt, const std::string &nlsParam) const
{
	if (m_isNull)
	{
		return "<NULL>";
	}
	else if (fmt.length() > 0)
	{
		int year;
		unsigned int month;
		unsigned int day;
		unsigned int hour = 0;
		unsigned int minute = 0;
		unsigned int second = 0;
		//		unsigned int fs = 0;

		GetLocalDate(year, month, day, hour, minute, second);
		//GetTime(hour, minute, second, fs);

		std::string tmpStr = fmt;

		dbd::ReplaceNumberToString(tmpStr, "yyyy", year, 4);
		dbd::ReplaceNumberToString(tmpStr, "MM", month, 2);
		dbd::ReplaceNumberToString(tmpStr, "dd", day, 2);
		dbd::ReplaceNumberToString(tmpStr, "hh", hour, 2);
		dbd::ReplaceNumberToString(tmpStr, "HH", hour, 2);
		dbd::ReplaceNumberToString(tmpStr, "mm", minute, 2);
		dbd::ReplaceNumberToString(tmpStr, "ss", (int) second, 2);

		return tmpStr;
	}
	else
	{
		char str[128];
		struct tm ltr;
		//struct tm *ptr = localtime_r(&m_time, &ltr);
		struct tm *ptr = persist_my_localtime_r(&m_time, -persist_get_local_timezone(), &ltr);

		strftime(str, 127, fmt.c_str(), ptr);

		return str;
	}
}

void Date::FromText(const std::string &datestr, const std::string &fmt,
		const std::string &nlsParam)
{
	int year = atoi(datestr.substr(0, 4).c_str());
	unsigned int month = atoi(datestr.substr(5, 2).c_str());
	unsigned int day = atoi(datestr.substr(8, 2).c_str());
	//	unsigned int hour = atoi(timestmpStr.substr(11, 2).c_str());
	//	unsigned int minute = atoi(timestmpStr.substr(14, 2).c_str());
	//	unsigned int second = atoi(timestmpStr.substr(17, 2).c_str());

	SetDate(year, month, day);
	//	SetTime(hour, minute, second, 0);
}

Date& Date::operator=(const Date &d)
{
	m_time = d.m_time;
	m_isNull = d.m_isNull;
	return *this;
}

Date Date::AddMonths(int i) const
{
	struct tm ltr;
	//struct tm *ptr = localtime_r(&m_time, &ltr);
	struct tm *ptr = persist_my_localtime_r(&m_time, -persist_get_local_timezone(), &ltr);

	ptr->tm_year += i / 12;
	ptr->tm_mon += i % 12;

	time_t t = mktime(ptr);

	return t;
}

Date Date::AddDays(int i) const
{
	return m_time + i * 24 * 3600;
}

Date Date::LastDay() const
{
	return AddDays(-1);
}

Date Date::NextDay() const
{
	return AddDays(1);
}

void Date::SetNull()
{
	m_isNull = true;
}

bool Date::IsNull() const
{
	return m_isNull;
}

std::string Date::ToBytes()
{
	return std::string((const char *) &m_time, sizeof(time_t));
}
int Date::FromBytes(std::string &buffer, int start_pos)
{
	memcpy(&m_time, buffer.c_str() + start_pos, sizeof(time_t));
	return sizeof(time_t);
}

Timestamp::Timestamp() :
	m_isNull(false)
{
	time_t ltime;
	time(&ltime);
	struct tm ltr;
	struct tm *ptr = persist_my_gmtime_r(&ltime, &ltr);

	m_year = ptr->tm_year + 1900;
	m_month = ptr->tm_mon + 1;
	m_day = ptr->tm_mday;
	m_hour = ptr->tm_hour;
	m_minute = ptr->tm_min;
	m_second = ptr->tm_sec;
	m_fs = 0;
}

Timestamp::Timestamp(time_t t) :
	m_isNull(false)
{
	struct tm ltr;
	struct tm *ptr = persist_my_gmtime_r(&t, &ltr);

	m_year = ptr->tm_year + 1900;
	m_month = ptr->tm_mon + 1;
	m_day = ptr->tm_mday;
	m_hour = ptr->tm_hour;
	m_minute = ptr->tm_min;
	m_second = ptr->tm_sec;
	m_fs = 0;
}

Timestamp::Timestamp(double epochTime) :
	m_isNull(false)
{
	long l = epochTime + 68569 + 0.5;
	long n = (4 * l) / 146097;
	l -= (146097 * n + 3) / 4;

	long i = (4000 * (l + 1)) / 1461001;
	l -= (1461 * i) / 4 + 31;

	long j = (80 * l) / 2447;

	unsigned day = l - (2447 * j) / 80;
	l = j / 11;
	int year = 100 * (n - 49) + i + l;
	unsigned month = j + 2 - (12 * l);

	long jc = epochTime;
	double ad = epochTime - jc - 0.5;
	if (ad < 0.0)
	{
		ad += 1.0;
	}
	unsigned int hour = ad * 24;
	unsigned int minute = ad * 1440 - hour * 60;
	unsigned int second = ad * 86400 - hour * 3600 - minute * 60;

	SetDate(year, month, day);
	SetTime(hour, minute, second, 0);
}

Timestamp::Timestamp(int year, unsigned int month, unsigned int day,
		unsigned int hour, unsigned int min, unsigned int sec, unsigned int fs) :
	m_isNull(false)
{
	m_year = year;
	m_month = month;
	m_day = day;
	m_hour = hour;
	m_minute = min;
	m_second = sec;
	m_fs = fs;
	SetLocalDate(year, month, day);
	SetLocalTime(hour, min, sec, fs);
}

Timestamp::Timestamp(const Timestamp &src)
{
	m_year = src.m_year;
	m_month = src.m_month;
	m_day = src.m_day;
	m_hour = src.m_hour;
	m_minute = src.m_minute;
	m_second = src.m_second;
	m_fs = src.m_fs;
	m_isNull = src.m_isNull;
}

Timestamp::~Timestamp()
{

}

void Timestamp::GetTime(unsigned int &hour, unsigned int &minute,
		unsigned int &second, unsigned int &fs) const
{

	hour = m_hour;
	minute = m_minute;
	second = m_second;
	fs = m_fs;
}

void Timestamp::GetDate(int &year, unsigned int &month, unsigned int &day) const
{
	year = m_year;
	month = m_month;
	day = m_day;
}

void Timestamp::AddMonth(int monthSpan)
{
	int month = this->m_month += monthSpan -1;
	int iyear = 0;
	if (month < 0)
	{
		while (month < 0)
		{
			month += 12;
			iyear --;
		}
		m_month = month + 1;
		m_year -= iyear;
	}
	else
	{
		this->m_month = month + 1;
		this->m_year += ((int)this->m_month - 1) / 12;
		this->m_month = ((int)this->m_month - 1) % 12 + 1;
	}
}

unsigned int Timestamp::get_month_day_count(int iyear, int month)
{
	static int days[12] =
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && is_leap_year(iyear))
		return 29;
	else
		return days[month - 1];
}

bool Timestamp::is_leap_year(int iyear)
{
	if (iyear % 400 == 0 || (iyear % 4 == 0 && iyear % 100 != 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Timestamp::AddDay(int daySpan)
{
	int day = m_day + daySpan;
	int monthDayCount = get_month_day_count(m_year, m_month);
	if (day < 0)
	{
		while (day < 0)
		{
			AddMonth(-1);
			day += monthDayCount;
			monthDayCount = get_month_day_count(m_year, m_month);
		}
	}
	else if (day > monthDayCount)
	{
		while (day > monthDayCount)
		{
			AddMonth(1);
			day -= monthDayCount;
			monthDayCount = get_month_day_count(m_year, m_month);
		}
	}
	m_day = day;
}

void Timestamp::AddHour(int hourSpan)
{
	int hour = m_hour + hourSpan;
	//m_hour += hourSpan;
	int iday = 0;
	if (hour < 0)
	{
		while (hour < 0)
		{
			hour += 24;
			iday --;
		}
		m_hour = hour;
	}
	else
	{
		iday = hour / 24;
		m_hour = hour % 24;
	}

	AddDay(iday);
}

void Timestamp::AddMinute(int minuteSpan)
{
	int min = m_minute + minuteSpan;
	//m_minute += minuteSpan;
	int ihour = 0;
	if (min < 0)
	{
		while (min < 0)
		{
			min += 60;
			ihour --;
		}
		m_minute = min;
	}
	else
	{
		ihour = min / 24;
		m_minute = min % 24;
	}

	AddHour(ihour);
}

void Timestamp::AddSecond(double secondSpan)
{
	m_second += secondSpan;
	int iminute = ((long) m_second) / 60;
	m_second -= iminute * 60;

	AddMinute(iminute);
}

void Timestamp::GetLocalTime(unsigned int &hour, unsigned int &minute,
		unsigned int &second, unsigned int &fs) const
{
	Timestamp tmpTime(*this);
	tmpTime.AddHour(-persist_get_local_timezone()/3600);

	return tmpTime.GetTime(hour, minute, second, fs);
}

void Timestamp::GetLocalDate(int &year, unsigned int &month, unsigned int &day) const
{
	Timestamp tmpTime(*this);
	tmpTime.AddHour(-persist_get_local_timezone()/3600);

	return tmpTime.GetDate(year, month, day);
}

int Timestamp::GetYear()
{
	return m_year;
}

unsigned int Timestamp::GetMonth()
{
	return m_month;
}

unsigned int Timestamp::GetDay()
{
	return m_day;
}

unsigned int Timestamp::GetHour()
{
	return m_hour;
}

unsigned int Timestamp::GetMinute()
{
	return m_minute;
}

unsigned int Timestamp::GetSecond()
{
	return m_second;
}

std::string Timestamp::ToText(const std::string &fmt, unsigned int fsprec,
		const std::string &nlsParam) const
{
	if (m_isNull)
		return "<NULL>";
	std::string tmpStr = fmt;

	if (fmt.length() == 0)
	{
		tmpStr = "yyyy/MM/dd hh:mm:ss.m";
	}
	{
		int year;
		unsigned int month;
		unsigned int day;
		unsigned int hour;
		unsigned int minute;
		unsigned int second;
		unsigned int fs;

		GetLocalDate(year, month, day);
		GetLocalTime(hour, minute, second, fs);

		dbd::ReplaceNumberToString(tmpStr, "yyyy", year, 4);
		dbd::ReplaceNumberToString(tmpStr, "MM", month, 2);
		dbd::ReplaceNumberToString(tmpStr, "dd", day, 2);
		dbd::ReplaceNumberToString(tmpStr, "hh", hour, 2);
		dbd::ReplaceNumberToString(tmpStr, "HH", hour, 2);
		dbd::ReplaceNumberToString(tmpStr, "mm", minute, 2);
		dbd::ReplaceNumberToString(tmpStr, "ss", (int) second, 2);
		dbd::ReplaceNumberToString(tmpStr, "m", fs, 3);

		return tmpStr;
	}
}

void Timestamp::FromText(const std::string &timestmpStr,
		const std::string &fmt, const std::string &nlsParam)
{
	int year = atoi(timestmpStr.substr(0, 4).c_str());
	unsigned int month = atoi(timestmpStr.substr(5, 2).c_str());
	unsigned int day = atoi(timestmpStr.substr(8, 2).c_str());
	unsigned int hour = atoi(timestmpStr.substr(11, 2).c_str());
	unsigned int minute = atoi(timestmpStr.substr(14, 2).c_str());
	unsigned int second = atoi(timestmpStr.substr(17, 2).c_str());

	SetDate(year, month, day);
	SetTime(hour, minute, second, 0);
}

void Timestamp::SetTime(unsigned int hour, unsigned int minute,
		unsigned int second, unsigned int fs)
{
	m_hour = hour;
	m_minute = minute;
	m_second = second;

	m_fs = fs;
	m_isNull = false;
}

void Timestamp::SetDate(int year, unsigned int month, unsigned int day)
{
	m_year = year;
	m_month = month;
	m_day = day;

	//m_time = mktime(ptr);
	m_isNull = false;
}

void Timestamp::SetTime(time_t dt, double fs)
{
	struct tm ltr;
	struct tm *ptr = persist_my_gmtime_r(&dt, &ltr);

	m_year = ptr->tm_year + 1900;
	m_month = ptr->tm_mon + 1;
	m_day = ptr->tm_mday;
	m_hour = ptr->tm_hour;
	m_minute = ptr->tm_min;
	m_second = ptr->tm_sec;
	m_fs = fs;
}

void Timestamp::GetTime(time_t &dt, double &fs)
{
	unsigned int day = (m_year-1970)*365 + (m_year-1972)/4 + m_day;
	for (unsigned int i=0; i < m_month-1; i++)
	{
		day += get_month_day_count(m_year, i+1);
	}
	dt = (day * 24 * 3600 + m_hour * 3600 + m_minute * 60 + m_second);
	fs = m_fs;
}

void Timestamp::SetLocalTime(unsigned int hour, unsigned int minute,
		unsigned int second, unsigned int fs)
{
	int year;
	unsigned int month;
	unsigned int day;
	GetLocalDate(year, month, day);
	m_year = year;
	m_month = month;
	m_day = day;
	m_hour = hour;
	m_minute = minute;
	m_second = second;
	m_fs = fs;
	m_isNull = false;

	AddHour(persist_get_local_timezone()/3600);
}

void Timestamp::SetLocalDate(int year, unsigned int month, unsigned int day)
{
	unsigned int hour, minute, second, fs;
	GetLocalTime(hour, minute, second, fs);
	m_year = year;
	m_month = month;
	m_day = day;
	m_hour = hour;
	m_minute = minute;
	m_second = second;

	m_isNull = false;

	AddHour(persist_get_local_timezone()/3600);
}

Timestamp& Timestamp::operator =(const Timestamp &src)
{
	m_year = src.m_year;
	m_month = src.m_month;
	m_day = src.m_day;
	m_hour = src.m_hour;
	m_minute = src.m_minute;
	m_second = src.m_second;
	m_fs = src.m_fs;
	m_isNull = src.m_isNull;
	m_fs = src.m_fs;
	return *this;
}

void Timestamp::SetNull()
{
	m_isNull = true;
}

bool Timestamp::IsNull() const
{
	return m_isNull;
}

std::string Timestamp::ToBytes()
{
	char buffer[32];
	int pos = 0;

	int size = sizeof(m_year);
	memcpy(buffer + pos, &m_year, size);
	pos += size;

	size = sizeof(m_month);
	memcpy(buffer + pos, &m_month, size);
	pos += size;

	size = sizeof(m_day);
	memcpy(buffer + pos, &m_day, size);
	pos += size;

	size = sizeof(m_hour);
	memcpy(buffer + pos, &m_hour, size);
	pos += size;

	size = sizeof(m_minute);
	memcpy(buffer + pos, &m_minute, size);
	pos += size;

	size = sizeof(m_second);
	memcpy(buffer + pos, &m_second, size);
	pos += size;

	size = sizeof(m_fs);
	memcpy(buffer + pos, &m_fs, size);
	pos += size;

	size = sizeof(bool);
	memcpy(buffer + pos, &m_isNull, size);
	pos += size;

	return std::string(buffer, sizeof(time_t) + sizeof(double));
}
int Timestamp::FromBytes(std::string &buffer, int start_pos)
{
	int size = sizeof(m_year);
	memcpy(&m_year, buffer.c_str() + start_pos, size);
	start_pos += size;

	size = sizeof(m_month);
	memcpy(&m_month, buffer.c_str() + start_pos, size);
	start_pos += size;

	size = sizeof(m_day);
	memcpy(&m_day, buffer.c_str() + start_pos, size);
	start_pos += size;

	size = sizeof(m_hour);
	memcpy(&m_minute, buffer.c_str() + start_pos, size);
	start_pos += size;

	size = sizeof(m_minute);
	memcpy(&m_minute, buffer.c_str() + start_pos, size);
	start_pos += size;

	size = sizeof(m_second);
	memcpy(&m_second, buffer.c_str() + start_pos, size);
	start_pos += size;

	size = sizeof(m_fs);
	memcpy(&m_fs, buffer.c_str() + start_pos, size);
	start_pos += size;

	size = sizeof(bool);
	memcpy(&m_isNull, buffer.c_str() + start_pos, size);
	start_pos += size;

	return start_pos;
}
time_t Timestamp::GetTime()
{
	unsigned int day = (m_year-1970)*365 + (m_year-1972)/4 + m_day;
	for (unsigned int i=0; i < m_month-1; i++)
	{
		day += get_month_day_count(m_year, i+1);
	}
	return (day * 24 * 3600 + m_hour * 3600 + m_minute * 60 + m_second);
}

Lob::Lob() :
	m_pis(NULL), m_bNeedUpdate(true)
{
}

Lob::Lob(std::istream *pis) :
	m_pis(pis), m_bNeedUpdate(true)
{
}

Lob::Lob(std::string filename) :
	m_pis(NULL), m_bNeedUpdate(true), m_filename(filename)
{
}

Lob::Lob(const Lob& orig)
{
	m_pis = NULL;
	m_content = orig.m_content;
	m_bNeedUpdate = orig.m_bNeedUpdate;
	m_filename = orig.m_filename;
	//m_bNeedRelease = orig.m_bNeedRelease;
}
Lob::~Lob()
{
	if (m_pis != NULL)
	{
		if (dynamic_cast<std::ifstream *>(m_pis) != NULL)
		{
			dynamic_cast<std::ifstream *>(m_pis)->close();
		}
		delete m_pis;
	}
}
Lob &Lob::operator =(const Lob &orig)
{
	m_pis = NULL;
	m_bNeedUpdate = orig.m_bNeedUpdate;
	m_filename = orig.m_filename;
	m_content = orig.m_content;
	return *this;
}
bool Lob::IsNeedUpdate()
{
	return m_bNeedUpdate;
}
void Lob::SetNeedUpdate(bool bNeedUpdate)
{
	m_bNeedUpdate = bNeedUpdate;
}
bool Lob::IsNull()
{
	return m_content.empty() && m_filename == "";
}
std::istream *Lob::GetStream()
{
	if (m_pis != NULL)
	{
		if (dynamic_cast<std::ifstream *>(m_pis) != NULL)
		{
			dynamic_cast<std::ifstream *>(m_pis)->close();
		}
		delete m_pis;
	}
	if (m_filename != "")
	{
		m_pis = new std::ifstream(m_filename.c_str(), std::ios_base::in);
	}
	else
	{
		m_pis = new std::istringstream(m_content);
	}
	return m_pis;
}
void Lob::SetString(std::string &str)
{
	m_content = str;
	m_bNeedUpdate = false;
}

std::string Lob::GetFilename()
{
	return m_filename;
}
void Lob::SetFilename(std::string filename)
{
	m_filename = filename;
	m_bNeedUpdate = true;
}

void Lob::WriteToFile(std::string filename)
{
	std::ofstream ofile(filename.c_str());

	ofile.write(m_content.c_str(), m_content.size());
	ofile.close();
}

std::string Lob::ToString()

{
	return m_content;
}

Blob::~Blob()
{

}

Clob::~Clob()
{

}

AnyType::AnyType() :
	m_isNull(true)
{

}

AnyType::AnyType(const AnyType &srcNum)
{
	this->m_dataType = srcNum.m_dataType;
	this->m_strVal = srcNum.m_strVal;
	this->m_dateVal = srcNum.m_dateVal;
	this->m_timestampVal = srcNum.m_timestampVal;
	this->m_number = srcNum.m_number;
	this->m_isNull = srcNum.m_isNull;
	this->m_blob = srcNum.m_blob;
	this->m_clob = srcNum.m_clob;
}

AnyType::AnyType(double val) :
	m_isNull(false)
{
	this->m_number.dVal = val;
	this->m_dataType = DOUBLE;
}

AnyType::AnyType(long double val) :
	m_isNull(false)
{
	this->m_number.ldVal = val;
	this->m_dataType = DOUBLE;
}

AnyType::AnyType(float val) :
	m_isNull(false)
{
	this->m_number.fVal = val;
	this->m_dataType = FLOAT;
}

AnyType::AnyType(long val) :
	m_isNull(false)
{
	this->m_number.lVal = val;
	this->m_dataType = LONG;
}

AnyType::AnyType(int val) :
	m_isNull(false)
{
	this->m_number.iVal = val;
	this->m_dataType = INT;
}

AnyType::AnyType(short val) :
	m_isNull(false)
{
	this->m_number.sVal = val;
	this->m_dataType = SHORT;
}

AnyType::AnyType(unsigned char val) :
	m_isNull(false)
{
	this->m_number.ucVal = val;
	this->m_dataType = CHAR;
}

AnyType::AnyType(signed char val) :
	m_isNull(false)
{
	this->m_number.cVal = val;
	this->m_dataType = CHAR;
}

AnyType::AnyType(unsigned long val) :
	m_isNull(false)
{
	this->m_number.ulVal = val;
	this->m_dataType = LONG;
}

AnyType::AnyType(unsigned int val) :
	m_isNull(false)
{
	this->m_number.uiVal = val;
	this->m_dataType = INT;
}

AnyType::AnyType(unsigned short val) :
	m_isNull(false)
{
	this->m_number.usVal = val;
	this->m_dataType = SHORT;
}

AnyType::AnyType(std::string sval) :
	m_isNull(false)
{
	this->m_strVal = sval;
	this->m_dataType = STRING;
}

AnyType::AnyType(Date date) :
	m_isNull(false)
{
	this->m_dateVal = date;
	this->m_dataType = DATE;
}

AnyType::AnyType(Timestamp timestamp) :
	m_isNull(false)
{
	this->m_timestampVal = timestamp;
	this->m_dataType = TIMESTAMP;
}

AnyType::AnyType(Blob blob) :
	m_isNull(false)
{
	this->m_blob = blob;
	this->m_dataType = BLOB;
}

AnyType::AnyType(Clob clob) :
	m_isNull(false)
{
	this->m_clob = clob;
	this->m_dataType = CLOB;
}

AnyType::~AnyType()
{
	// if (m_pLob != NULL) delete m_pLob;
}

int AnyType::GetInt()
{
	switch (this->m_dataType)
	{
	case INT:
		return this->m_number.iVal;
	case SHORT:
		return this->m_number.sVal;
	case LONG:
		return this->m_number.lVal;
	case DOUBLE:
		return (long)this->m_number.dVal;
	default:
		break;
	}
	return this->m_number.iVal;
}

char AnyType::GetChar()
{
	return this->m_number.cVal;
}

long AnyType::GetLong()
{
	switch (this->m_dataType)
	{
	case INT:
		return this->m_number.iVal;
	case SHORT:
		return this->m_number.sVal;
	case LONG:
		return this->m_number.lVal;
	case DOUBLE:
		return (long)this->m_number.dVal;
	default:
		break;
	}
	return this->m_number.lVal;
}

short AnyType::GetShort()
{
	switch (this->m_dataType)
	{
	case INT:
		return this->m_number.iVal;
	case SHORT:
		return this->m_number.sVal;
	case LONG:
		return this->m_number.lVal;
	case DOUBLE:
		return (long)this->m_number.dVal;
	default:
		break;
	}
	return this->m_number.sVal;
}

long double AnyType::GetLDouble()
{
	return this->m_number.ldVal;
}

double AnyType::GetDouble()
{
	return this->m_number.dVal;
}

float AnyType::GetFloat()
{
	return this->m_number.fVal;
}

std::string &AnyType::GetString()
{
	return this->m_strVal;
}

unsigned int AnyType::GetUInt()
{
	return this->m_number.uiVal;
}

unsigned long AnyType::GetULong()
{
	return this->m_number.ulVal;
}

unsigned short AnyType::GetUShort()
{
	return this->m_number.usVal;
}

unsigned char AnyType::GetUChar()
{
	return this->m_number.ucVal;
}

Date &AnyType::GetDate()
{
	return this->m_dateVal;
}

Timestamp &AnyType::GetTimestamp()
{
	return this->m_timestampVal;
}

AnyType::DataType AnyType::GetType()
{
	return this->m_dataType;
}

Blob AnyType::GetBlob()
{
	return m_blob;
}
Clob AnyType::GetClob()
{
	return m_clob;
}

bool AnyType::IsNull()
{
	return m_isNull;
}

void AnyType::SetNull()
{
	m_isNull = true;
}

std::string AnyType::ToString()
{
	if (m_isNull)
		return "<NULL>";

	std::stringstream ss;
	switch (m_dataType)
	{
	case INT:
		ss << this->m_number.iVal;
		break;
	case CHAR:
		ss << this->m_number.cVal;
		break;
	case SHORT:
		ss << this->m_number.sVal;
		break;
	case LONG:
		ss << this->m_number.lVal;
		break;
	case DOUBLE:
		ss << this->m_number.dVal;
		break;
	case FLOAT:
		ss << this->m_number.fVal;
		break;
	case STRING:
		ss << this->m_strVal;
		break;
	case DATE:
		ss << this->m_dateVal.ToText();
		break;
	case TIMESTAMP:
		ss << this->m_timestampVal.ToText();
		break;
	case CLOB:
	{
		char buffer[1024];
		while (m_clob.GetStream() != NULL && !m_clob.GetStream()->eof())
		{
			m_clob.GetStream()->read(buffer, 1024);
			int n = m_clob.GetStream()->gcount();
			if (n == 0)
				break;
			ss << std::string(buffer, n);
		}
		break;
	}
	case BLOB:
	{
		char buffer[1024];
		while (m_blob.GetStream() != NULL && !m_blob.GetStream()->eof())
		{
			m_blob.GetStream()->read(buffer, 1024);
			int n = m_blob.GetStream()->gcount();
			if (n == 0)
				break;
			ss << std::string(buffer, n);
		}
		break;
	}
	default:
		break;
	}

	ss.flush();
	return ss.str();
}

}
