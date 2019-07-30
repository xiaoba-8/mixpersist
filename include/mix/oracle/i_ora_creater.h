/*
 * i_ora_creater.h
 *
 *  Created on: 2018-2-24
 *      Author: xiaoba-8
 */

#ifndef IORACREATER_H_
#define IORACREATER_H_

#include <occi.h>
#include <mix/database/i_creater.h>

namespace mix
{

class i_ora_creater: public i_creater
{
public:
	virtual ~i_ora_creater() {}
	virtual oracle::occi::Environment *GetEnvironment() = 0;
};

}
#endif /* ORACREATER_H_ */
