/*
 * User.cpp
 *
 *  Created on: Jul 26, 2019
 *      Author: xiaoba-8
 */

#include "User.h"

User::User() {

}

User::~User() {

}

int User::GetUserId()
{
	return m_id;
}

void User::SetUserId(int id)
{
	m_id = id;
}

std::string User::GetName()
{
	return m_name;
}

void User::SetName(std::string name)
{
	m_name = name;
}

std::string User::GetPassword()
{
	return m_password;
}

void User::SetPassword(std::string password)
{
	m_password = password;
}

UserDEF g_userDef =
{
	"tbl_user",
	{
		new mix::column_def<int, User>("user_id", &User::GetUserId, &User::SetUserId, true, true),
		new mix::column_def<std::string, User>("name", &User::GetName, &User::SetName, false),
		new mix::column_def<std::string, User>("password", &User::GetPassword, &User::SetPassword, false)
	}
};

mix::Dao<UserDEF> g_userDao(g_userDef);
