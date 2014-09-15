/******************************************************************************/
/*  File        : lz_datetime.h   	                                          */
/*  Description : LaZy datetime header                                        */
/*  Written     : 2013.05                                                     */
/*  Version     : 0.1                                                         */
/*  Author      : LaZyDev                                                     */
/*  Contacts    : chriskr7@gmail.com                                          */
/******************************************************************************/


/**
 *	@file lz_datetime.h
 *	@author LaZy
 *	@date May 2013
 *	@version 0.1
 *	@brief Header defines datetime structure & related func
 */


#ifndef __LZ_DATETIME_H__
#define __LZ_DATETIME_H__

#include <time.h>
#include <pthread.h>
#include "lz_typeconv.h"

#define SEC_OF_DAY		86400


struct lz_date_interface;

/**
 *	@struct __lz_date
 *	@brief LaZy date structure
 *	@var typedef struct __lz_date _lz_date
 */
typedef struct tag_lz_date{
	int year;							/**< year YYYY						*/
	int month;							/**< month MM						*/
	int day;							/**< day DD							*/
	struct lz_date_interface* pthis;	/**< pointer to methods				*/
} lz_date;

typedef lz_date* p_lz_date;				/**< typedef						*/


/**
 *	@struct lz_date_interface
 *	@brief LaZy lz_date_interface fp
 */
struct lz_date_interface{
	void (*get_localdate)(p_lz_date);
	char* (*to_string)(p_lz_date, char*);
	char* (*to_fmt_string)(p_lz_date, char*);
	int (*to_int)(p_lz_date);
	void (*from_int)(p_lz_date, int);
	void (*from_string)(p_lz_date, char*);
	void (*from_tm)(p_lz_date, struct tm*);
	int (*prev_date)(p_lz_date, p_lz_date, int);
	int (*next_date)(p_lz_date, p_lz_date, int);
	int (*weekday)(p_lz_date);
	char* (*weekday_str)(p_lz_date);
};


#ifdef __cplusplus
extern "C"{
#endif

void lz_date_init(p_lz_date p_date);
void lz_date_get_localdate(p_lz_date p_date);
char* lz_date_to_string(p_lz_date p_date, char* str);
char* lz_date_to_fmt_string(p_lz_date p_date, char* str);
int lz_date_to_int(p_lz_date p_date);
void lz_date_from_int(p_lz_date p_date, int ival);
void lz_date_from_string(p_lz_date p_date, char* str);
void lz_date_from_tm(p_lz_date p_date, struct tm* p_tm);
int lz_date_prev_date(p_lz_date p_bdate, p_lz_date p_pdate, int prev);
int lz_date_next_date(p_lz_date p_bdate, p_lz_date p_ndate, int next);
int lz_date_weekday(p_lz_date p_date);
char* lz_date_weekday_str(p_lz_date p_date);
p_lz_date new_lz_date();
void delete_lz_date(p_lz_date p_date);

#ifdef __cplusplus
}
#endif

static struct lz_date_interface lz_date_method_tbl =
{
	lz_date_get_localdate,
	lz_date_to_string,
	lz_date_to_fmt_string,
	lz_date_to_int,
	lz_date_from_int,
	lz_date_from_string,
	lz_date_from_tm,
	lz_date_prev_date,
	lz_date_next_date,
	lz_date_weekday,
	lz_date_weekday_str
};



/*-----------------------------------------------------------------------------*/



struct lz_time_interface;

/**
 *	@struct __lz_time
 *	@brief LaZy time structure
 *	@var typedef struct __lz_time _lz_time
 */
typedef struct tag_lz_time{
	int hour;							/**< hour 0-23						*/
	int min;							/**< minutes 0-59					*/
	int sec;							/**< seconds 0-59					*/
	int mille_sec;						/**< mille seconds 0-999			*/
	struct lz_time_interface* pthis;	/**< pointer to methods				*/
} lz_time;

typedef lz_time* p_lz_time;				/**< typedef						*/


/**
 *	@struct lz_time_interface
 *	@brief LaZy time lz_time_interface fp
 */
struct lz_time_interface{
	void (*get_localtime)(p_lz_time);
	char* (*to_string)(p_lz_time, char*);
	char* (*to_fmt_string)(p_lz_time, char*);
	char* (*to_stringm)(p_lz_time, char*);
	char* (*to_fmt_stringm)(p_lz_time, char*);
	int (*to_int)(p_lz_time);
	int (*to_intm)(p_lz_time);
	void (*from_int)(p_lz_time, int);
	void (*from_intm)(p_lz_time, int);
	void (*from_string)(p_lz_time, char*);
	void (*from_stringm)(p_lz_time, char*);
	void (*from_tm)(p_lz_time, struct tm*);
};


#ifdef __cplusplus
extern "C"{
#endif

void lz_time_init(p_lz_time p_time);
void lz_time_get_localtime(p_lz_time p_time);
char* lz_time_to_string(p_lz_time p_time, char* str);
char* lz_time_to_fmt_string(p_lz_time p_time, char* str);
char* lz_time_to_stringm(p_lz_time p_time, char* str);
char* lz_time_to_fmt_stringm(p_lz_time p_time, char* str);
int lz_time_to_int(p_lz_time p_time);
int lz_time_to_intm(p_lz_time p_time);
void lz_time_from_int(p_lz_time p_time, int ival);
void lz_time_from_intm(p_lz_time p_time, int ival);
void lz_time_from_string(p_lz_time p_time, char* str);
void lz_time_from_stringm(p_lz_time p_time, char* str);
void lz_time_from_tm(p_lz_time p_time, struct tm* p_tm);
p_lz_time new_lz_time();
void delete_lz_time(p_lz_time p_time);

#ifdef __cplusplus
}
#endif


static struct lz_time_interface lz_time_method_tbl =
{
	lz_time_get_localtime,
	lz_time_to_string,
	lz_time_to_fmt_string,
	lz_time_to_stringm,
	lz_time_to_fmt_stringm,
	lz_time_to_int,
	lz_time_to_intm,
	lz_time_from_int,
	lz_time_from_intm,
	lz_time_from_string,
	lz_time_from_stringm,
	lz_time_from_tm
};





/*-----------------------------------------------------------------------------*/






struct lz_datetime_interface;

/**
 *	@struct __lz_datetime
 *	@brief LaZy datetime structure
 *	@var typedef struct __lz_datetime _lz_datetime
 */
typedef struct tag_lz_datetime{
	int year;								/**< year YYYY						*/
	int month;								/**< month MM						*/
	int day;								/**< day DD							*/
	int hour;								/**< hour 0-23						*/
	int min;								/**< minutes 0-59					*/
	int sec;								/**< seconds 0-59					*/
	int mille_sec;							/**< mille seconds 0-999			*/
	struct lz_datetime_interface* pthis; 	/**< pointer to methods				*/
} lz_datetime;

typedef lz_datetime* p_lz_datetime;			/**< typedef						*/


/**
 *	@struct lz_datetime_method
 *	@brief LaZy datetime method fp
 */
struct lz_datetime_interface{
	void (*get_ldatetime)(p_lz_datetime);
	char* (*to_string)(p_lz_datetime, char*);
	char* (*to_fmt_string)(p_lz_datetime, char*);
	char* (*to_stringm)(p_lz_datetime, char*);
	char* (*to_fmt_stringm)(p_lz_datetime, char*);
	void (*from_string)(p_lz_datetime, char*);
	void (*from_stringm)(p_lz_datetime, char*);
	void (*to_tm)(p_lz_datetime, struct tm*);
	void (*from_tm)(p_lz_datetime, struct tm*);
	void (*to_datetime)(p_lz_datetime, p_lz_date, p_lz_time);
	void (*to_date)(p_lz_datetime, p_lz_date);
	void (*to_time)(p_lz_datetime, p_lz_time);
	void (*from_datetime)(p_lz_datetime, p_lz_date, p_lz_time);
};


#ifdef __cplusplus
extern "C"{
#endif

void lz_datetime_init(p_lz_datetime p_dt);
void lz_datetime_get_ldatetime(p_lz_datetime p_dt);
char* lz_datetime_to_string(p_lz_datetime p_dt, char* str);
char* lz_datetime_to_fmt_string(p_lz_datetime p_dt, char* str);
char* lz_datetime_to_stringm(p_lz_datetime p_dt, char* str);
char* lz_datetime_to_fmt_stringm(p_lz_datetime p_dt, char* str);
void lz_datetime_from_string(p_lz_datetime p_dt, char* str);
void lz_datetime_from_stringm(p_lz_datetime p_dt, char* str);
void lz_datetime_to_tm(p_lz_datetime p_dt, struct tm* p_tm);
void lz_datetime_from_tm(p_lz_datetime p_dt, struct tm* p_tm);
void lz_datetime_to_datetime(p_lz_datetime p_dt, p_lz_date p_date, p_lz_time p_time);
void lz_datetime_to_date(p_lz_datetime p_dt, p_lz_date p_date);
void lz_datetime_to_time(p_lz_datetime p_dt, p_lz_time p_time);
void lz_datetime_from_datetime(p_lz_datetime p_dt, p_lz_date p_date, p_lz_time p_time);
p_lz_datetime new_lz_datetime();
void delete_lz_datetime(p_lz_datetime p_dt);

#ifdef __cplusplus
}
#endif


static struct lz_datetime_interface lz_datetime_method_tbl =
{
	lz_datetime_get_ldatetime,
	lz_datetime_to_string,
	lz_datetime_to_fmt_string,
	lz_datetime_to_stringm,
	lz_datetime_to_fmt_stringm,
	lz_datetime_from_string,
	lz_datetime_from_stringm,
	lz_datetime_to_tm,
	lz_datetime_from_tm,
	lz_datetime_to_datetime,
	lz_datetime_to_date,
	lz_datetime_to_time,
	lz_datetime_from_datetime
};



#ifdef __cplusplus
extern "C"{
#endif

void convert_datetime_kor(p_lz_datetime src_dt, char* src_tz, p_lz_datetime kor_dt);
void convert_datetime(p_lz_datetime src_dt, char* src_tz, p_lz_datetime out_dt, char* out_tz);
void dt_lock(int onoff);

#ifdef __cplusplus
}
#endif


#endif	/* __LZ_DATETIME_H__ */
