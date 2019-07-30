/*
 * User.h
 *
 *  Created on: Jul 26, 2019
 *      Author: xiaoba-8
 */

#ifndef USER_H_
#define USER_H_

#include <mix/database/dbdatas.h>
#include <mix/persist/dao_helper.h>
#include <mix/persist/persist.hpp>

typedef mix::entity_def<3, int, std::string, std::string> UserDEF;

class User
{
public:
	typedef UserDEF  DefType;

public:
	User();
	virtual ~User();

	int GetUserId();
	void SetUserId(int id);

	std::string GetName();
	void SetName(std::string name);

	std::string GetPassword();
	void SetPassword(std::string password);

private:
	int m_id;
	std::string m_name;
	std::string m_password;
};


extern UserDEF g_userDef;
extern mix::Dao<UserDEF> g_userDao;

namespace mix
{

template<>
inline Dao<UserDEF> &dao_helper::GetDao<User, UserDEF>()
{
	return g_userDao;
}

}

#endif /* USER_H_ */
