/*
 * dbdatas.h
 *
 *  Created on: 2018-2-25
 *      Author: xiaoba-8
 */

#ifndef DBDATAS_H_
#define DBDATAS_H_

#include <stdint.h>
#include <string.h>
#include <string>

#include <time.h>

namespace mix
{

enum LobOpenMode
{
	LOB_READONLY = 1,
	LOB_READWRITE = 2,
	LOB_WRITEONLY = 3,
	LOB_APPENDONLY = 4,
	LOB_FULLOVERWRITE = 5,
	LOB_FULLREAD = 6
};


class Date
{
public:
	Date();
	Date(time_t t);
	Date(int year, unsigned int month, unsigned int day, unsigned int hour = 0,
			unsigned int minute = 0, unsigned int seconds = 0);
	Date(const Date &a);
	virtual ~Date();

	virtual void SetDate(int year = 1, unsigned int month = 1,
			unsigned int day = 1, unsigned int hour = 0,
			unsigned int minute = 0, unsigned int seconds = 0);
	virtual void GetDate(int &year, unsigned int &month, unsigned int &day,
			unsigned int &hour, unsigned int &min, unsigned int &sec) const;
	virtual void SetLocalDate(int year = 1, unsigned int month = 1,
			unsigned int day = 1, unsigned int hour = 0,
			unsigned int minute = 0, unsigned int seconds = 0);
	virtual void GetLocalDate(int &year, unsigned int &month,
			unsigned int &day, unsigned int &hour, unsigned int &min,
			unsigned int &sec) const;
	virtual std::string ToText(const std::string &fmt = "yyyy-MM-dd HH:mm:ss",
			const std::string &nlsParam = "") const;
	virtual void FromText(const std::string &datestr,
			const std::string &fmt = "", const std::string &nlsParam = "");
	virtual Date& operator=(const Date &d);
	virtual Date AddMonths(int i) const;
	virtual Date AddDays(int i) const;
	virtual Date LastDay() const;
	virtual Date NextDay() const;

	virtual void SetNull();
	virtual bool IsNull() const;

	virtual std::string ToBytes();
	virtual int FromBytes(std::string &buffer, int start_pos=0);

	time_t GetTime() const
	{
		return m_time;
	}
private:

	time_t m_time;
	bool m_isNull;
};

class Timestamp
{
public:
	Timestamp();
	Timestamp(time_t t);
	Timestamp(double epochTime);
	Timestamp(int year, unsigned int month, unsigned int day,
			unsigned int hour = 0, unsigned int min = 0, unsigned int sec = 0,
			unsigned int fs = 0);
	Timestamp(const Timestamp &src);
	virtual ~Timestamp();

	virtual void GetTime(unsigned int &hour, unsigned int &minute,
			unsigned int &second, unsigned int &fs) const;
	virtual void
			GetDate(int &year, unsigned int &month, unsigned int &day) const;

	virtual int GetYear();
	virtual unsigned int GetMonth();
	virtual unsigned int GetDay();
	virtual unsigned int GetHour();
	virtual unsigned int GetMinute();
	virtual unsigned int GetSecond();

	virtual void GetLocalTime(unsigned int &hour, unsigned int &minute,
			unsigned int &second, unsigned int &fs) const;
	virtual void
			GetLocalDate(int &year, unsigned int &month, unsigned int &day) const;

	virtual std::string ToText(const std::string &fmt = "%Y-%m-%d %H:%M:%S",
			unsigned int fsprec = 0, const std::string &nlsParam = "") const;
	virtual void FromText(const std::string &timestmpStr,
		const std::string &fmt = "%Y-%m-%d %H:%M:%S", const std::string &nlsParam = "");

	virtual void SetTime(unsigned int hour, unsigned int minute,
			unsigned int second, unsigned int fs);
	virtual void SetDate(int year, unsigned int month, unsigned int day);

	virtual void SetTime(time_t dt, double ms);
	virtual void GetTime(time_t &dt, double &ms);

	virtual void SetLocalTime(unsigned int hour, unsigned int minute,
			unsigned int second, unsigned int fs);
	virtual void SetLocalDate(int year, unsigned int month, unsigned int day);

	virtual Timestamp& operator =(const Timestamp &src);

	virtual void SetNull();
	virtual bool IsNull() const;

	virtual std::string ToBytes();
	virtual int FromBytes(std::string &buffer, int start_pos=0);

	time_t GetTime();
	unsigned int GetFs()
	{
		return m_fs;
	}
	unsigned int GetMs()
	{
		return m_fs/1000000;
	}
	void AddMonth(int monthSpan);
	void AddDay(int daySpan);
	void AddHour(int hourSpan);
	void AddMinute(int minuteSpan);
	void AddSecond(double secondSpan);

private:
	unsigned int get_month_day_count(int iyear, int month);

	bool is_leap_year(int iyear);

	int m_year;
	unsigned int m_month;
	unsigned int m_day;
	unsigned int m_hour;
	unsigned int m_minute;
	unsigned int m_second;
	unsigned int m_fs;
	bool m_isNull;
};

template<typename T>
class Number
{
private:
	T m_value;
	bool m_isNull;
public:
	Number() :
		m_isNull(true)
	{
	}
	Number(const Number<T> &orig)
	{
		m_value = orig.m_value;
		m_isNull = orig.m_isNull;
	}
	Number(T value, bool isNull=false) :
		m_isNull(isNull)
	{
		m_value = value;
	}
	virtual ~Number()
	{
	}

	void SetValue(T value)
	{
		m_isNull = false;
		m_value = value;
	}

	bool IsNull()
	{
		return m_isNull;
	}

	void SetNull()
	{
		m_isNull = true;
	}

	T Value()
	{
		return m_value;
	}

	Number<T> &operator =(const T value)
	{
		m_isNull = false;
		m_value = value;
		return *this;
	}

	Number<T> &operator =(const Number<T> &orig)
	{
		m_isNull = orig.m_isNull;
		m_value = orig.m_value;
		return *this;
	}

	Number<T> operator + (const T &n)
	{
		Number<T> b;
		b.m_isNull = this->m_isNull;
		b.m_value = m_value + n;
		return b;
	}

	Number<T> operator + (const Number<T> &n)
	{
		Number<T> b;
		b.m_isNull = this->m_isNull || n.m_isNull;
		b.m_value = m_value + n.m_value;
		return b;
	}

	Number<T> operator - (const T &n)
	{
		Number<T> b;
		b.m_isNull = this->m_isNull;
		b.m_value = m_value - n;
		return b;
	}
	Number<T> operator - (const Number<T> &n)
	{
		Number<T> b;
		b.m_isNull = this->m_isNull || n.m_isNull;
		b.m_value = m_value - n.m_value;
		return b;
	}

	Number<T> operator * (const T &n)
	{
		Number<T> b;
		b.m_isNull = this->m_isNull;
		b.m_value = m_value * n;
		return b;
	}
	Number<T> operator * (const Number<T> &n)
	{
		Number<T> b;
		b.m_isNull = this->m_isNull || n.m_isNull;
		b.m_value = m_value * n.m_value;
		return b;
	}

	Number<T> operator / (const T &n)
	{
		Number<T> b;
		b.m_isNull = this->m_isNull;
		b.m_value = m_value / n;
		return b;
	}
	Number<T> operator / (const Number<T> &n)
	{
		Number<T> b;
		b.m_isNull = this->m_isNull || n.m_isNull;
		b.m_value = m_value / n.m_value;
		return b;
	}

	operator T() const
	{
		if (m_isNull) return 0;
		return m_value;
	}

	virtual std::string ToBytes()
	{
		char buffer[128];
		buffer[0] = (char)m_isNull;
		memcpy(buffer+1, &m_value, sizeof(T));

		return std::string(buffer, sizeof(T)+1);
	}
	virtual int FromBytes(std::string &buffer, int start_pos=0)
	{
		m_isNull = buffer.at(start_pos);
		memcpy(&m_value, buffer.c_str()+1+start_pos, sizeof(T));
		return 1+sizeof(T);
	}
};

typedef Number<int> Integer;
typedef Number<long> Long;
typedef Number<float> Float;
typedef Number<double> Double;
typedef Number<unsigned int> UInteger;
typedef Number<uint64_t> UInt64;

class Lob
{
public:
	Lob();
	Lob(std::string filename);
	Lob(std::istream *pis);
	Lob(const Lob &orig);
	virtual ~Lob();

	Lob &operator =(const Lob &orig);

	bool IsNull();
	std::istream *GetStream();
	void SetString(std::string &str);
	std::string GetFilename();
	void SetFilename(std::string filename);

	virtual bool IsNeedUpdate();
	virtual void SetNeedUpdate(bool bNeedUpdate);
	std::string ToString();

	virtual void WriteToFile(std::string filename);
protected:
	std::istream	*m_pis;
	bool m_bNeedUpdate;
	std::string m_filename;
	std::string m_content;
};

class Blob : public Lob
{
public:
	Blob() : Lob() {}
	Blob(std::string filename) : Lob(filename) {}
	Blob(std::istream *pis) : Lob(pis) {}
	Blob(const Lob &orig) : Lob((const Blob &)orig) {}
	virtual ~Blob();
};

class Clob : public Lob
{
public:
	Clob() : Lob() {}
	Clob(std::string filename) : Lob(filename) {}
	Clob(std::istream *pis) : Lob(pis) {}
	Clob(const Lob &orig) : Lob((const Clob &)orig) {}
	virtual ~Clob();
};

class AnyType
{
public:
	enum DataType
	{
		INT,
		CHAR,
		SHORT,
		LONG,
		DOUBLE,
		FLOAT,
		STRING,
		DATE,
		TIMESTAMP,
		CLOB,
		BLOB
	};

	AnyType(const AnyType &srcNum);
	AnyType(long double val);
	AnyType(double val);
	AnyType(float val);
	AnyType(long val);
	AnyType(int val);
	AnyType(short val);
	AnyType(unsigned char val);
	AnyType(signed char val);
	AnyType(unsigned long val);
	AnyType(unsigned int val);
	AnyType(unsigned short val);

	AnyType(std::string sval);
	AnyType(Date date);
	AnyType(Timestamp timestamp);
	AnyType(Blob blob);
	AnyType(Clob clob);
	AnyType();

	virtual ~AnyType();

	int GetInt();
	char GetChar();
	long GetLong();
	short GetShort();
	double GetDouble();
	long double GetLDouble();
	float GetFloat();
	std::string &GetString();
	Blob GetBlob();
	Clob GetClob();

	unsigned int GetUInt();
	unsigned long GetULong();
	unsigned short GetUShort();
	unsigned char GetUChar();

	Date &GetDate();
	Timestamp &GetTimestamp();

	DataType GetType();

	bool IsNull();

	void SetNull();

	std::string ToString();

private:

	bool m_isNull;
	DataType m_dataType;
	std::string m_strVal;
	Date m_dateVal;
	Timestamp m_timestampVal;
	Blob m_blob;
	Clob m_clob;
	union _number
	{
		signed char cVal;
		long lVal;
		int iVal;
		long double ldVal;
		double dVal;
		short sVal;
		float fVal;
		unsigned char ucVal;
		unsigned long ulVal;
		unsigned int uiVal;
		unsigned short usVal;
	} m_number;
};

}

#endif /* DBDATAS_H_ */
