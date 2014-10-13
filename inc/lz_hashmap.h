/******************************************************************************/
/*  File        : lz_hashmap.h                                                */
/*  Description : LaZy hashmap                                                */
/*  Written     : 2013.05                                                     */
/*  Version     : 0.1                                                         */
/*  Author      : LaZy                                                        */
/*  Contacts    : chriskr7@gmail.com                                          */
/******************************************************************************/


/**
 *	@file lz_hashmap.h
 *	@author LaZy
 *	@date May 2013
 *	@version 0.1
 *	@brief Header defines lz_hashmap
 */

#ifndef __LZ_HASHMAP_H__
#define __LZ_HASHMAP_H__

#define LZ_HASHMAP_THREAD_SAFE

#include <stdint.h>
#include <stdbool.h>
#ifdef LZ_HASHMAP_THREAD_SAFE
#include <semaphore.h>
#endif


#define LZ_HASHMAP_LOT_SIZE (2 << 11)
#define LZ_HASHMAP_GROWTH_RATE 2

typedef void* lz_key;
typedef void* lz_value;


typedef struct tag_lz_pair{
	lz_key k;
	lz_value v;
} _lz_pair;


struct lz_hashmap_interface;

typedef struct tag_lz_hashmap{
	_lz_pair* map;
	uint32_t size;
	uint32_t capa;
	struct lz_hashmap_interface* pthis;
#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_t lock;
#endif
} _lz_hashmap;


struct lz_hashmap_interface
{
	bool (*set)(_lz_hashmap*, lz_key, lz_value);
	lz_value (*get)(_lz_hashmap*, lz_key);
	bool (*remove)(_lz_hashmap*, lz_key, _lz_pair*);
	bool (*remove_x)(_lz_hashmap*, lz_key);
	char* (*to_string)(_lz_hashmap*, char*);
};


#ifdef __cplusplus
extern "C"{
#endif

void lz_hashmap_init(_lz_hashmap* p_lzh);
void lz_hashmap_init_x(_lz_hashmap* p_lzh, int sz);
void lz_hashmap_initialize(_lz_hashmap* p_lzh);
void lz_hashmap_initialize_x(_lz_hashmap* p_lzh, int sz);
void lz_hashmap_put(_lz_pair* map, uint32_t sz, uint32_t (*hash_func)(lz_key), lz_key k, lz_value v);
uint32_t lz_hashmap_func(lz_key k);
bool lz_hashmap_equal(lz_key k1, lz_key k2);
bool lz_hashmap_inflate(_lz_hashmap* p_lzh);
bool lz_hashmap_set(_lz_hashmap* p_lzh, lz_key k, lz_value v);
lz_value lz_hashmap_get(_lz_hashmap* p_lzh, lz_key k);
int lz_hashmap_get_pos(_lz_hashmap* p_lzh, lz_key k);
void lz_hashmap_rearrange(_lz_hashmap* p_lzh, _lz_pair* tmp);
void lz_hashmap_rearrange_x(_lz_hashmap* p_lzh, _lz_pair* tmp);
void lz_hashmap_cleanup(_lz_hashmap* p_lzh);
bool lz_hashmap_remove(_lz_hashmap* p_lzh, lz_key k, _lz_pair* lp);
bool lz_hashmap_remove_x(_lz_hashmap* p_lzh, lz_key k);
char* lz_hashmap_to_string(_lz_hashmap* p_lzh, char* str);
_lz_hashmap* new_lz_hashmap();
_lz_hashmap* new_lz_hashmap_x(int sz);
void delete_lz_hashmap(_lz_hashmap* p_lzh);

#ifdef __cplusplus
}
#endif

static struct lz_hashmap_interface lz_hashmap_method_tbl =
{
	lz_hashmap_set,
	lz_hashmap_get,
	lz_hashmap_remove,
	lz_hashmap_remove_x,
	lz_hashmap_to_string
};


#endif	/* __LZ_HASHMAP_H__ */