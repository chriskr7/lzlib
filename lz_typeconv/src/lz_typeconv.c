/******************************************************************************/
/*  File        : lz_typeconv.h   	                                          */
/*  Description : LaZy typeconv                                               */
/*  Written     : 2013.05                                                     */
/*  Version     : 0.1                                                         */
/*  Author      : LaZyDev                                                     */
/*  Contacts    : chriskr7@gmail.com                                          */
/******************************************************************************/


/**
 *	@file lz_typeconv.c
 *	@author LaZy
 *	@date May 2013
 *	@version 0.1
 *	@brief define type conversion related function
 */

#include <stdlib.h>
#include "lz_typeconv.h"


int lz_str_2_int(char* buf, int len)
{
	int ret = 0;
	int stx = 0, i;
	char minus_f = 0;

	while(*(buf+stx) == ' ')
		stx++;

	switch(*(buf+stx)){
		case '-':
			minus_f = 1;
		case '+':
			stx++;
			break;
	}

	if(*(buf+stx) < '0' || *(buf+stx) > '9')
		exit(EXIT_FAILURE);

	for(i = stx; i < len; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9')
			ret = ret * 10 + (*(buf+i) - '0');
		else
			break;
	}

	return minus_f ? ((~ret)+1) : ret;
}


long lz_str_2_long(char* buf, int len)
{
	long ret = 0;
	int stx = 0, i;
	char minus_f = 0;

	while(*(buf+stx) == ' ')
		stx++;

	switch(*(buf+stx)){
		case '-':
			minus_f = 1;
		case '+':
			stx++;
			break;
	}

	if(*(buf+stx) < '0' || *(buf+stx) > '9')
		exit(EXIT_FAILURE);

	for(i = stx; i < len; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9')
			ret = ret * 10 + (*(buf+i) - '0');
		else
			break;
	}

	return minus_f ? ((~ret)+1) : ret;
}


long long lz_str_2_llong(char* buf, int len)
{
	long long ret = 0;
	int stx = 0, i;
	char minus_f = 0;

	while(*(buf+stx) == ' ')
		stx++;

	switch(*(buf+stx)){
		case '-':
			minus_f = 1;
		case '+':
			stx++;
			break;
	}

	if(*(buf+stx) < '0' || *(buf+stx) > '9')
		exit(EXIT_FAILURE);

	for(i = stx; i < len; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9')
			ret = ret * 10 + (*(buf+i) - '0');
		else
			break;
	}

	return minus_f ? ((~ret)+1) : ret;
}


float lz_str_2_float(char* buf, int len)
{
	float ret = 0.0F, lvalue = 0.0F, mvalue = 0.0F;
	int stx = 0, exp_cnt = 0, i;
	char minus_f = 0;

	while(*(buf+stx) == ' ')
		stx++;

	switch(*(buf+stx)){
		case '-':
			minus_f = 1;
		case '+':
			stx++;
			break;
	}

	if(*(buf+stx) < '0' || *(buf+stx) > '9')
		exit(EXIT_FAILURE);

	for(i = stx; i < len; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9')
			lvalue = lvalue * 10 + (*(buf+i) - '0');
		else
			break;
	}

	if(*(buf+i) == '.') i++;
	else return ret;

	if(*(buf+i) < '0' || *(buf+i) > '9')
		exit(EXIT_FAILURE);

	for(; i < len; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9'){
			mvalue = mvalue * 10 + (*(buf+i) - '0');
			exp_cnt--;
		}
		else
			break;
	}

	mvalue = (mvalue * powf(10, exp_cnt));
	ret = (lvalue + mvalue);

	return minus_f ? (ret*-1) : ret;
}


float lz_str_2_float_decimal(char* buf, int len, int no_of_decimal)
{
	float ret = 0.0F, lvalue = 0.0F, mvalue = 0.0F;
	int stx = 0, exp_cnt = 0, i;
	char minus_f = 0;

	while(*(buf+stx) == ' ')
		stx++;

	switch(*(buf+stx)){
		case '-':
			minus_f = 1;
		case '+':
			stx++;
			break;
	}

	if(*(buf+stx) < '0' || *(buf+stx) > '9')
		exit(EXIT_FAILURE);

	for(i = stx; i < len; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9')
			lvalue = lvalue * 10 + (*(buf+i) - '0');
		else
			break;
	}

	if(*(buf+i) == '.') i++;
	else return ret;

	if(*(buf+i) < '0' || *(buf+i) > '9')
		exit(EXIT_FAILURE);

	no_of_decimal += i;

	for(; i < no_of_decimal; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9'){
			mvalue = mvalue * 10 + (*(buf+i) - '0');
			exp_cnt--;
		}
		else
			break;
	}

	mvalue = (mvalue * powf(10, exp_cnt));
	ret = (lvalue + mvalue);

	return minus_f ? (ret*-1) : ret;
}


double lz_str_2_double(char* buf, int len)
{
	double ret = 0.0F, lvalue = 0.0F, mvalue = 0.0F;
	int stx = 0, exp_cnt = 0, i;
	char minus_f = 0;

	while(*(buf+stx) == ' ')
		stx++;

	switch(*(buf+stx)){
		case '-':
			minus_f = 1;
		case '+':
			stx++;
			break;
	}

	if(*(buf+stx) < '0' || *(buf+stx) > '9')
		exit(EXIT_FAILURE);

	for(i = stx; i < len; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9')
			lvalue = lvalue * 10 + (*(buf+i) - '0');
		else
			break;
	}

	if(*(buf+i) == '.') i++;
	else return ret;

	if(*(buf+i) < '0' || *(buf+i) > '9')
		exit(EXIT_FAILURE);

	for(; i < len; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9'){
			mvalue = mvalue * 10 + (*(buf+i) - '0');
			exp_cnt--;
		}
		else
			break;
	}

	mvalue = (mvalue * powf(10, exp_cnt));
	ret = (lvalue + mvalue);

	return minus_f ? (ret*-1) : ret;
}


double lz_str_2_double_decimal(char* buf, int len, int no_of_decimal)
{
	double ret = 0.0F, lvalue = 0.0F, mvalue = 0.0F;
	int stx = 0, exp_cnt = 0, i;
	char minus_f = 0;

	while(*(buf+stx) == ' ')
		stx++;

	switch(*(buf+stx)){
		case '-':
			minus_f = 1;
		case '+':
			stx++;
			break;
	}

	if(*(buf+stx) < '0' || *(buf+stx) > '9')
		exit(EXIT_FAILURE);

	for(i = stx; i < len; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9')
			lvalue = lvalue * 10 + (*(buf+i) - '0');
		else
			break;
	}

	if(*(buf+i) == '.') i++;
	else return ret;

	if(*(buf+i) < '0' || *(buf+i) > '9')
		exit(EXIT_FAILURE);

	no_of_decimal += i;

	for(; i < no_of_decimal; i++){
		if(*(buf+i) >= '0' && *(buf+i) <= '9'){
			mvalue = mvalue * 10 + (*(buf+i) - '0');
			exp_cnt--;
		}
		else
			break;
	}

	mvalue = (mvalue * powf(10, exp_cnt));
	ret = (lvalue + mvalue);

	return minus_f ? (ret*-1) : ret;
}


void lz_int_2_leading_zero_str(char* buf, int len, int ival)
{
	char fb[20], wb[20];
	sprintf(fb, "%%0%dd", len);
	sprintf(wb, fb, ival);
	memcpy(buf, wb, len);
}
