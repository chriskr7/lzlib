/******************************************************************************/
/*  File        : lz_typeconv.h   	                                          */
/*  Description : LaZy typeconv header                                        */
/*  Written     : 2013.05                                                     */
/*  Version     : 0.1                                                         */
/*  Author      : LaZyDev                                                     */
/*  Contacts    : chriskr7@gmail.com                                          */
/******************************************************************************/


/**
 *	@file lz_typeconv.h
 *	@author LaZy
 *	@date May 2013
 *	@version 0.1
 *	@brief Header declares type conversion related function
 */


#ifndef __LZ_TYPECONV_H__
#define __LZ_TYPECONV_H__

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>


#ifdef __cplusplus
extern "C"{
#endif


/**
 *	string to integer
 *	@param	buf		string to be converted into integer
 *	@param	len		length of string to be converted
 *	@return	the converted integer
 */
__inline int lz_str_2_int(char* buf, int len);


/**
 *	string to long
 *	@param	buf		string to be converted into long
 *	@param	len		length of string to be converted
 *	@return	the converted long
 */
long lz_str_2_long(char* buf, int len);


/**
 *	string to long long
 *	@param	buf		string to be converted into long long
 *	@param	len		length of string to be converted
 *	@return	the converted long long
 */
long long lz_str_2_llong(char* buf, int len);


/**
 *	string to float
 *	@param	buf		string to be converted into float
 *	@param	len		length of string to be converted
 *	@return	the converted float
 */
float lz_str_2_float(char* buf, int len);


/**
 *	string to float
 *	@param	buf				string to be converted into float
 *	@param	len				length of string to be converted
 *	@param	no_of_decimal	# of decimal to be converted
 *	@return	the converted float
 */
float lz_str_2_float_decimal(char* buf, int len, int no_of_decimal);


/**
 *	string to double
 *	@param	buf		string to be converted into double
 *	@param	len		length of string to be converted
 *	@return	the converted double
 */
double lz_str_2_double(char* buf, int len);


/**
 *	string to double
 *	@param	buf				string to be converted into double
 *	@param	len				length of string to be converted
 *	@param	no_of_decimal	# of decimal to be converted
 *	@return	the converted double
 */
double lz_str_2_double_decimal(char* buf, int len, int no_of_decimal);


/**
 *	int to leading zero string
 *	@param	buf				string the integer is to be placed
 *	@param	len				length of string to be copied
 *	@param	ival			integer value to be placed in string
 */
void lz_int_2_leading_zero_str(char* buf, int len, int ival);


#ifdef __cplusplus
}
#endif



#endif	/* __LZ_TYPECONV_H__ */
