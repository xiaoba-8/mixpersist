/*
 * hibernate_mysql_demo.cpp
 *
 *  Created on: Jul 26, 2019
 *      Author: xiaoba-8
 */

//#include <mysql/mysql.h>

#include <stdio.h>
#include <mix/database/dbdatas.h>
#include <mix/database/sql_exception.h>
#include <mix/mysql/mysql_creater.h>

#include "User.h"

/***************************************************
 *
create table tbl_user (
    user_id bigint NOT NULL auto_increment,
    name varchar(64) NOT NULL,
    password varchar(64) DEFAULT NULL,
    PRIMARY KEY (user_id)
    );
 *
 **************************************************/

int main(int argc, char *argv[])
{
	mix::mysql_creater creater("mysql", "username", "password", "tcp://127.0.0.1:3306/usertest");
	creater.Register();

	mix::dao_helper dao;
	User user1;

	user1.SetName("test");
	user1.SetPassword("test");

	std::vector<User *> users;

	try
	{
		dao.Insert(user1);

		dao.SearchEntityByCondition("1=1", users, 0, 100);

		for (int i = 0; i < (int)users.size(); ++i)
		{
			User *pItem = users[i];
			printf("Fetch user[%d] name=%s password = %s\n", i, pItem->GetName().c_str(), pItem->GetPassword().c_str());
		}
	}
	catch (mix::sql_exception &ex)
	{
		printf("Error : %s\n", ex.what());
	}

	return 0;
}
