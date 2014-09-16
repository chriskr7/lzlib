/******************************************************************************/
/*  File        : lz_util.h                                                   */
/*  Description : LaZy util header                                            */
/*  Written     : 2013.05                                                     */
/*  Version     : 0.1                                                         */
/*  Author      : LaZyDev                                                     */
/*  Contacts    : chriskr7@gmail.com                                          */
/******************************************************************************/


/**
 *	@file lz_util.h
 *	@author LaZy
 *	@date May 2013
 *	@version 0.1
 *	@brief Header defines utils
 */

#ifndef __LZ_UTIL_H__
#define __LZ_UTIL_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif

void lz_log(const char* file_path, const char* file_name, char* src_file, int line, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif	/* __LZ_UTIL_H__ */
