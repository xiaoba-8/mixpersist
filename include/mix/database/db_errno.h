/*
 * db_errno.h
 *
 *  Created on: 2018-4-21
 *      Author: xiaoba-8
 */

#ifndef DB_ERRNO_H_
#define DB_ERRNO_H_

#define DATABASE_PREFIX	0
#define DATABASE_NUMBER	40000

#define DATABASE_NO_CREATER_NO						40001
#define DATABASE_NO_CREATER_MSG						"No Database Creater!"

#define DATABASE_CLOSED								40101

#define DATABASE_CONNECTION_CREATE					40102
#define DATABASE_CONNECTION_DESTROY					40103

#define DATABASE_STATEMENT_CREATE					40104
#define DATABASE_PRESTATEMENT_CREATE				40105
#define DATABASE_STATEMENT_CLOSE					40106

#define DATABASE_ORACREATER_CONDUCT					40107

#define DATABASE_RESULTSET_WRONGCOL					40108

#define DATABASE_QUERY								40109
#define DATABASE_UPDATE								40110
#define DATABASE_NOTSUPPORT							40111

#define DATABASE_TRANSACTION_COMMIT					40112
#define DATABASE_TRANSACTION_ROLLBACK				40113


#endif /* DB_ERRNO_H_ */
