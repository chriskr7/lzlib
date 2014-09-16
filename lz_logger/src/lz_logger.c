/******************************************************************************/
/*  File        : lz_logger.c   	                                          */
/*  Description : LaZy logger                                                 */
/*  Written     : 2013.05                                                     */
/*  Version     : 0.1                                                         */
/*  Author      : LaZyDev                                                     */
/*  Contacts    : chriskr7@gmail.com                                          */
/******************************************************************************/


/**
 *	@file lz_logger.c
 *	@author LaZy
 *	@date May 2013
 *	@version 0.1
 *	@brief Defines log function
 */

#include <stdarg.h>
#include "lz_logger.h"
#include "lz_datetime.h"

void lz_log(const char* file_path, const char* file_name, char* src_file, int line, const char* fmt, ...)
{
	FILE* log_fp;

	va_list vl;
	char file_nm[128];
	char t_buf[32];
	char log_msg[1024*4];

	lz_date today;
	lz_date_init(&today);
	lz_time now;
	lz_time_init(&now);

	today.pthis->get_localdate(&today);

	sprintf(file_nm, "%s/%s_%d%02d%02d", file_path, file_name, today.year, today.month, today.day);

	log_fp = fopen(file_nm, "a");
	if(log_fp == NULL){
		return;
	}

	va_start(vl, fmt);
	vsprintf(log_msg, fmt, vl);
	va_end(vl);

	now.pthis->get_localtime(&now);
	fprintf(log_fp, "[%s][%s:%d]\t%s\n", now.pthis->to_fmt_stringm(&now, t_buf), src_file, line, log_msg);
	fclose(log_fp);
}
