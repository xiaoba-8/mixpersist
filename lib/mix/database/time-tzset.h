/*
 * time-tzset.h
 *
 *  Created on: 2018-4-11
 *      Author: xiaoba-8
 */

#ifndef TIME_TZSET_H_
#define TIME_TZSET_H_

#ifdef __cplusplus
extern "C" {
#endif

int persist_get_local_timezone();

struct tm *persist_my_gmtime_r (const time_t *__restrict __timer, struct tm *__restrict __tp);
struct tm *persist_my_localtime_r (const time_t *__restrict __timer, int timezone, struct tm *__restrict __tp);

#ifdef __cplusplus
}
#endif

#endif /* TIME_TZSET_H_ */
