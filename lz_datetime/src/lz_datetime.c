/******************************************************************************/
/*  File        : lz_datetime.c   	                                          */
/*  Description : LaZy datetime                                               */
/*  Written     : 2013.05                                                     */
/*  Version     : 0.1                                                         */
/*  Author      : LaZyDev                                                     */
/*  Contacts    : chriskr7@gmail.com                                          */
/******************************************************************************/


/**
 *	@file lz_datetime.c
 *	@author LaZy
 *	@date May 2013
 *	@version 0.1
 *	@brief Defines datetime related function
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/timeb.h>
#include "lz_datetime.h"


/*------------------------------------------
 *
 *		lz_date interface
 *
 *-----------------------------------------*/

void lz_date_init(p_lz_date p_date)
{
	p_date->pthis = &lz_date_method_tbl;
}


void lz_date_get_localdate(p_lz_date p_date)
{
	struct tm ltm;
	time_t ltime;

	time(&ltime);
	localtime_r(&ltime, &ltm);

	p_date->year = (ltm.tm_year + 1900);
	p_date->month = (ltm.tm_mon + 1);
	p_date->day = ltm.tm_mday;
}


char* lz_date_to_string(p_lz_date p_date, char* str)
{
	sprintf(str, "%04d%02d%02d", p_date->year, p_date->month, p_date->day);
	return str;
}


char* lz_date_to_fmt_string(p_lz_date p_date, char* str)
{
	sprintf(str, "%04d-%02d-%02d", p_date->year, p_date->month, p_date->day);
	return str;
}


int lz_date_to_int(p_lz_date p_date)
{
	return (p_date->year * 10000 + p_date->month * 100 + p_date->day);
}


void lz_date_from_int(p_lz_date p_date, int ival)
{
	p_date->year = ival / 10000;
	p_date->month = ((ival % 10000) / 100);
	p_date->day = ((ival % 10000) % 100);
}


void lz_date_from_string(p_lz_date p_date, char* str)
{
	p_date->year = lz_str_2_int(str, 4);
	p_date->month = lz_str_2_int(str+4, 2);
	p_date->day = lz_str_2_int(str+6, 2);
}


void lz_date_from_tm(p_lz_date p_date, struct tm* p_tm)
{
	p_date->year = (p_tm->tm_year + 1900);
	p_date->month = (p_tm->tm_mon + 1);
	p_date->day = p_tm->tm_mday;
}


int lz_date_prev_date(p_lz_date p_bdate, p_lz_date p_pdate, int prev)
{
	struct tm btm;
	time_t btime;

	btm.tm_year = (p_bdate->year - 1900);
	btm.tm_mon = (p_bdate->month - 1);
	btm.tm_mday = p_bdate->day;
	btm.tm_hour = 0;
	btm.tm_min = 0;
	btm.tm_sec = 1;
	btm.tm_isdst = -1;

	btime = mktime(&btm);
	if(btime == -1){
		return -1;
	}

	btime -= (prev * SEC_OF_DAY);

	localtime_r(&btime, &btm);
	lz_date_from_tm(p_pdate, &btm);

	return 0;
}


int lz_date_next_date(p_lz_date p_bdate, p_lz_date p_ndate, int next)
{
	struct tm btm;
	time_t btime;

	btm.tm_year = (p_bdate->year - 1900);
	btm.tm_mon = (p_bdate->month - 1);
	btm.tm_mday = p_bdate->day;
	btm.tm_hour = 0;
	btm.tm_min = 0;
	btm.tm_sec = 1;
	btm.tm_isdst = -1;

	btime = mktime(&btm);
	if(btime == -1){
		return -1;
	}

	btime += (next * SEC_OF_DAY);

	localtime_r(&btime, &btm);
	lz_date_from_tm(p_ndate, &btm);

	return 0;
}


int lz_date_weekday(p_lz_date p_date)
{
	struct tm btm;
	time_t btime;

	btm.tm_year = (p_date->year - 1900);
	btm.tm_mon = (p_date->month - 1);
	btm.tm_mday = p_date->day;
	btm.tm_hour = 0;
	btm.tm_min = 0;
	btm.tm_sec = 1;
	btm.tm_isdst = -1;

	btime = mktime(&btm);
	if(btime == -1){
		return -1;
	}

	localtime_r(&btime, &btm);

	return btm.tm_wday;
}


char* lz_date_weekday_str(p_lz_date p_date)
{
	static char* weekdays[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
	return weekdays[lz_date_weekday(p_date)];
}


p_lz_date new_lz_date()
{
	p_lz_date p_date = NULL;
	p_date = (p_lz_date)malloc(sizeof(lz_date));
	if(p_date)
		p_date->pthis = &lz_date_method_tbl;

	return p_date;
}


void delete_lz_date(p_lz_date p_date)
{
	if(p_date)
		free(p_date);
}




/*------------------------------------------
 *
 *		lz_time interface
 *
 *-----------------------------------------*/

void lz_time_init(p_lz_time p_time)
{
	p_time->pthis = &lz_time_method_tbl;
}


void lz_time_get_localtime(p_lz_time p_time)
{
	struct tm ltm;
	struct timeb ltb;

	ftime(&ltb);
	localtime_r(&ltb.time, &ltm);

	p_time->hour = ltm.tm_hour;
	p_time->min = ltm.tm_min;
	p_time->sec = ltm.tm_sec;
	p_time->mille_sec = ltb.millitm;
}


char* lz_time_to_string(p_lz_time p_time, char* str)
{
	sprintf(str, "%02d%02d%02d", p_time->hour, p_time->min, p_time->sec);
	return str;
}


char* lz_time_to_fmt_string(p_lz_time p_time, char* str)
{
	sprintf(str, "%02d:%02d:%02d", p_time->hour, p_time->min, p_time->sec);
	return str;
}


char* lz_time_to_stringm(p_lz_time p_time, char* str)
{
	sprintf(str, "%02d%02d%02d%03d", p_time->hour, p_time->min, p_time->sec, p_time->mille_sec);
	return str;
}


char* lz_time_to_fmt_stringm(p_lz_time p_time, char* str)
{
	sprintf(str, "%02d:%02d:%02d.%03d", p_time->hour, p_time->min, p_time->sec, p_time->mille_sec);
	return str;
}


int lz_time_to_int(p_lz_time p_time)
{
	return (p_time->hour * 10000 + p_time->min * 100 + p_time->sec);
}


int lz_time_to_intm(p_lz_time p_time)
{
	return (p_time->hour * 10000000 + p_time->min * 100000 + p_time->sec * 1000 + p_time->mille_sec);
}


void lz_time_from_int(p_lz_time p_time, int ival)
{
	p_time->hour = ival / 10000;
	p_time->min = ((ival % 10000) / 100);
	p_time->sec = ((ival % 10000) % 100);
}


void lz_time_from_intm(p_lz_time p_time, int ival)
{
	p_time->hour = ival / 10000000;
	p_time->min = ((ival % 10000000) / 100000);
	p_time->sec = ((ival % 10000000) % 100000) / 1000;
	p_time->mille_sec = ((ival % 10000000) % 100000) % 1000;
}


void lz_time_from_string(p_lz_time p_time, char* str)
{
	p_time->hour = lz_str_2_int(str, 2);
	p_time->min = lz_str_2_int(str+2, 2);
	p_time->sec = lz_str_2_int(str+4, 2);
}


void lz_time_from_stringm(p_lz_time p_time, char* str)
{
	p_time->hour = lz_str_2_int(str, 2);
	p_time->min = lz_str_2_int(str+2, 2);
	p_time->sec = lz_str_2_int(str+4, 2);
	p_time->mille_sec = lz_str_2_int(str+6, 3);
}


void lz_time_from_tm(p_lz_time p_time, struct tm* p_tm)
{
	p_time->hour = p_tm->tm_hour;
	p_time->min = p_tm->tm_min;
	p_time->sec = p_tm->tm_sec;
}


p_lz_time new_lz_time()
{
	p_lz_time p_time = NULL;
	p_time = (p_lz_time)malloc(sizeof(lz_time));
	if(p_time)
		p_time->pthis = &lz_time_method_tbl;

	return p_time;
}


void delete_lz_time(p_lz_time p_time)
{
	if(p_time)
		free(p_time);
}





/*------------------------------------------
 *
 *		lz_datetime interface
 *
 *-----------------------------------------*/

void lz_datetime_init(p_lz_datetime p_dt)
{
	p_dt->pthis = &lz_datetime_method_tbl;
}


void lz_datetime_get_ldatetime(p_lz_datetime p_dt)
{
	struct tm ltm;
	struct timeb ltb;

	ftime(&ltb);
	localtime_r(&ltb.time, &ltm);

	p_dt->year = (ltm.tm_year + 1900);
	p_dt->month = (ltm.tm_mon + 1);
	p_dt->day = ltm.tm_mday;
	p_dt->hour = ltm.tm_hour;
	p_dt->min = ltm.tm_min;
	p_dt->sec = ltm.tm_sec;
	p_dt->mille_sec = ltb.millitm;
}


char* lz_datetime_to_string(p_lz_datetime p_dt, char* str)
{
	sprintf(str, "%04d%02d%02d%02d%02d%02d",
		p_dt->year, p_dt->month, p_dt->day, p_dt->hour, p_dt->min, p_dt->sec);
	return str;
}


char* lz_datetime_to_fmt_string(p_lz_datetime p_dt, char* str)
{
	sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d",
		p_dt->year, p_dt->month, p_dt->day, p_dt->hour, p_dt->min, p_dt->sec);
	return str;
}


char* lz_datetime_to_stringm(p_lz_datetime p_dt, char* str)
{
	sprintf(str, "%04d%02d%02d%02d%02d%02d%03d",
		p_dt->year, p_dt->month, p_dt->day, p_dt->hour, p_dt->min, p_dt->sec, p_dt->mille_sec);
	return str;
}


char* lz_datetime_to_fmt_stringm(p_lz_datetime p_dt, char* str)
{
	sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
		p_dt->year, p_dt->month, p_dt->day, p_dt->hour, p_dt->min, p_dt->sec, p_dt->mille_sec);
	return str;
}


void lz_datetime_from_string(p_lz_datetime p_dt, char* str)
{
	p_dt->year = lz_str_2_int(str, 4);
	p_dt->month = lz_str_2_int(str+4, 2);
	p_dt->day = lz_str_2_int(str+6, 2);
	p_dt->hour = lz_str_2_int(str+8, 2);
	p_dt->min = lz_str_2_int(str+10, 2);
	p_dt->sec = lz_str_2_int(str+12, 2);
}


void lz_datetime_from_stringm(p_lz_datetime p_dt, char* str)
{
	p_dt->year = lz_str_2_int(str, 4);
	p_dt->month = lz_str_2_int(str+4, 2);
	p_dt->day = lz_str_2_int(str+6, 2);
	p_dt->hour = lz_str_2_int(str+8, 2);
	p_dt->min = lz_str_2_int(str+10, 2);
	p_dt->sec = lz_str_2_int(str+12, 2);
	p_dt->mille_sec = lz_str_2_int(str+14, 3);
}


void lz_datetime_to_tm(p_lz_datetime p_dt, struct tm* p_tm)
{
	p_tm->tm_year = (p_dt->year - 1900);
	p_tm->tm_mon = (p_dt->month -1);
	p_tm->tm_mday = p_dt->day;
	p_tm->tm_hour = p_dt->hour;
	p_tm->tm_min = p_dt->min;
	p_tm->tm_sec = p_dt->sec;
}


void lz_datetime_from_tm(p_lz_datetime p_dt, struct tm* p_tm)
{
	p_dt->year = (p_tm->tm_year + 1900);
	p_dt->month = (p_tm->tm_mon + 1);
	p_dt->day = p_tm->tm_mday;
	p_dt->hour = p_tm->tm_hour;
	p_dt->min = p_tm->tm_min;
	p_dt->sec = p_tm->tm_sec;
}


void lz_datetime_to_datetime(p_lz_datetime p_dt, p_lz_date p_date, p_lz_time p_time)
{
	p_date->year = p_dt->year;
	p_date->month = p_dt->month;
	p_date->day = p_dt->day;

	p_time->hour = p_dt->hour;
	p_time->min = p_dt->min;
	p_time->sec = p_dt->sec;
	p_time->mille_sec = p_dt->mille_sec;
}


void lz_datetime_to_date(p_lz_datetime p_dt, p_lz_date p_date)
{
	p_date->year = p_dt->year;
	p_date->month = p_dt->month;
	p_date->day = p_dt->day;
}


void lz_datetime_to_time(p_lz_datetime p_dt, p_lz_time p_time)
{
	p_time->hour = p_dt->hour;
	p_time->min = p_dt->min;
	p_time->sec = p_dt->sec;
	p_time->mille_sec = p_dt->mille_sec;
}


void lz_datetime_from_datetime(p_lz_datetime p_dt, p_lz_date p_date, p_lz_time p_time)
{
	p_dt->year = p_date->year;
	p_dt->month = p_date->month;
	p_dt->day = p_date->day;
	p_dt->hour = p_time->hour;
	p_dt->min = p_time->min;
	p_dt->sec = p_time->sec;
	p_dt->mille_sec = p_time->mille_sec;
}


p_lz_datetime new_lz_datetime()
{
	p_lz_datetime p_dt = NULL;
	p_dt = (p_lz_datetime)malloc(sizeof(lz_datetime));
	if(p_dt)
		p_dt->pthis = &lz_datetime_method_tbl;

	return p_dt;
}


void delete_lz_datetime(p_lz_datetime p_dt)
{
	if(p_dt)
		free(p_dt);
}


void convert_datetime_kor(p_lz_datetime src_dt, char* src_tz, p_lz_datetime kor_dt)
{
	struct tm mytm;
	time_t mytime;
	char buf[80];

	sprintf(buf, "TZ=%s", src_tz);
	dt_lock(1);
	putenv(buf);
	tzset();
	lz_datetime_to_tm(src_dt, &mytm);
	mytime = mktime(&mytm);

	memset(buf, 0x00, 80);
	sprintf(buf, "TZ=Asia/Seoul");
	putenv(buf);
	tzset();
	localtime_r(&mytime, &mytm);
	dt_lock(0);

	lz_datetime_from_tm(kor_dt, &mytm);
}


void convert_datetime(p_lz_datetime src_dt, char* src_tz, p_lz_datetime out_dt, char* out_tz)
{
	struct tm mytm;
	time_t mytime;
	char buf[80];

	sprintf(buf, "TZ=%s", src_tz);
	dt_lock(1);
	putenv(buf);
	tzset();
	lz_datetime_to_tm(src_dt, &mytm);
	mytime = mktime(&mytm);

	memset(buf, 0x00, 80);
	sprintf(buf, "TZ=%s", out_tz);
	putenv(buf);
	tzset();
	localtime_r(&mytime, &mytm);
	dt_lock(0);

	lz_datetime_from_tm(out_dt, &mytm);
}


void dt_lock(int onoff)
{
	static pthread_mutex_t dt_mutex;
	static int initialized = 0;
	static char tz[80];

	if(!initialized){
		if(pthread_mutex_init(&dt_mutex, NULL) == 0)
			initialized = 1;
	}

	if(onoff){
		pthread_mutex_lock(&dt_mutex);
	}
	else{
		putenv("TZ=Asia/Seoul");
		tzset();
		pthread_mutex_unlock(&dt_mutex);
	}
}
