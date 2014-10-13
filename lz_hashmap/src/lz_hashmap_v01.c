/******************************************************************************/
/*  File        : lz_hashmap.c                                                */
/*  Description : LaZy hashmap                                                */
/*  Written     : 2013.05                                                     */
/*  Version     : 0.1                                                         */
/*  Author      : LaZy                                                        */
/*  Contacts    : chriskr7@gmail.com                                          */
/******************************************************************************/


/**
 *	@file lz_hashmap.c
 *	@author LaZy
 *	@date May 2013
 *	@version 0.1
 *	@brief Defines lz_hashmap
 */

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "lz_hashmap.h"


void lz_hashmap_init(_lz_hashmap* p_lzh)
{
	p_lzh->pthis = &lz_hashmap_method_tbl;
	p_lzh->map = (_lz_pair*)malloc(sizeof(_lz_pair) * LZ_HASHMAP_LOT_SIZE);
	memset(p_lzh->map, 0x00, sizeof(_lz_pair) * LZ_HASHMAP_LOT_SIZE);
	p_lzh->size = 0;
	p_lzh->capa = LZ_HASHMAP_LOT_SIZE;
#ifdef LZ_HASHMAP_THREAD_SAFE
	if(sem_init(&p_lzh->lock, 0, 1) != 0)
		exit(EXIT_FAILURE);
#endif
}


void lz_hashmap_init_x(_lz_hashmap* p_lzh, int sz)
{
	p_lzh->pthis = &lz_hashmap_method_tbl;
	p_lzh->map = (_lz_pair*)malloc(sizeof(_lz_pair) * sz);
	memset(p_lzh->map, 0x00, sizeof(_lz_pair) * sz);
	p_lzh->size = 0;
	p_lzh->capa = sz;
#ifdef LZ_HASHMAP_THREAD_SAFE
	if(sem_init(&p_lzh->lock, 0, 1) != 0)
		exit(EXIT_FAILURE);
#endif
}


void lz_hashmap_initialize(_lz_hashmap* p_lzh)
{
	p_lzh->map = (_lz_pair*)malloc(sizeof(_lz_pair) * LZ_HASHMAP_LOT_SIZE);
	memset(p_lzh->map, 0x00, sizeof(_lz_pair) * LZ_HASHMAP_LOT_SIZE);
	p_lzh->size = 0;
	p_lzh->capa = LZ_HASHMAP_LOT_SIZE;
#ifdef LZ_HASHMAP_THREAD_SAFE
	if(sem_init(&p_lzh->lock, 0, 1) != 0)
		exit(EXIT_FAILURE);
#endif
}


void lz_hashmap_initialize_x(_lz_hashmap* p_lzh, int sz)
{
	p_lzh->map = (_lz_pair*)malloc(sizeof(_lz_pair) * sz);
	memset(p_lzh->map, 0x00, sizeof(_lz_pair) * sz);
	p_lzh->size = 0;
	p_lzh->capa = sz;
#ifdef LZ_HASHMAP_THREAD_SAFE
	if(sem_init(&p_lzh->lock, 0, 1) != 0)
		exit(EXIT_FAILURE);
#endif
}


void lz_hashmap_put(_lz_pair* map, uint32_t sz, uint32_t (*hash_func)(lz_key), lz_key k, lz_value v)
{
	static uint32_t hash;
	hash = (*hash_func)(k) % sz;
	
	while(map[hash].v != NULL)
		hash = (hash + 1) % sz;
	
	map[hash].k = k;
	map[hash].v = v;
}


bool lz_hashmap_inflate(_lz_hashmap* p_lzh)
{
	_lz_pair* tmp = (_lz_pair*)malloc(sizeof(_lz_pair) * p_lzh->capa * LZ_HASHMAP_GROWTH_RATE);
	memset(tmp, 0x00, (sizeof(_lz_pair) * p_lzh->capa * LZ_HASHMAP_GROWTH_RATE));
	if(tmp == NULL)
		return false;
	
	p_lzh->capa *= LZ_HASHMAP_GROWTH_RATE;
	lz_hashmap_rearrange(p_lzh, tmp);
	
	free(p_lzh->map);
	p_lzh->map = tmp;

	return true;
}


void lz_hashmap_rearrange(_lz_hashmap* p_lzh, _lz_pair* tmp)
{
	static uint32_t i;
	
	for(i = 0; i < (p_lzh->capa / LZ_HASHMAP_GROWTH_RATE); i++)
		if(p_lzh->map[i].v != NULL)
			lz_hashmap_put(tmp, p_lzh->capa, lz_hashmap_func, p_lzh->map[i].k, p_lzh->map[i].v);
}


void lz_hashmap_rearrange_x(_lz_hashmap* p_lzh, _lz_pair* tmp)
{
	static uint32_t i;
	
	for(i = 0; i < p_lzh->capa; i++)
		if(p_lzh->map[i].v != NULL)
			lz_hashmap_put(tmp, p_lzh->capa, lz_hashmap_func, p_lzh->map[i].k, p_lzh->map[i].v);
}


uint32_t lz_hashmap_func(lz_key k)
{
	
	static uint32_t hash;

#ifdef LZ_HASHMAP_INT
	/* Robert Jenkins' 32bit integer hash */
	hash = *((uint32_t*)k);
	hash = (hash+0x7ed55d16) + (hash << 12);
	hash = (hash^0xc761c23c) ^ (hash >> 19);
	hash = (hash+0x165667b1) + (hash << 5);
	hash = (hash+0xd3a2646c) ^ (hash << 9);
	hash = (hash+0xfd7046c5) + (hash << 3);
	hash = (hash^0xb55a4f09) ^ (hash >> 16);
#else
	/* Dan Bernstein' string hash(djb2) */
	static unsigned char c;
	hash = 5381;
	
	while(c != '\0'){
		c = *(unsigned char*)k++;
		hash = ((hash << 5) + hash) + c;
	}
#endif
	
	return hash;
}


bool lz_hashmap_equal(lz_key k1, lz_key k2)
{
#ifdef LZ_HASHMAP_INT
	return *((int*)k1) == *((int*)k2) ? true : false;
#else
	return (strcmp((char*)k1, (char*)k2) == 0) ? true : false;
#endif
}


bool lz_hashmap_set(_lz_hashmap* p_lzh, lz_key k, lz_value v)
{
	static uint32_t i = 1;
	
	/* key duplicate check */
	if(lz_hashmap_get(p_lzh, k) != NULL){
		return false;
	}
	
#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_wait(&p_lzh->lock);
#endif
	
	/* 0.7 due to performance */
	if( ((float)p_lzh->size) / p_lzh->capa > 0.70)
		if(!lz_hashmap_inflate(p_lzh)){
#ifdef LZ_HASHMAP_THREAD_SAFE
			sem_post(&p_lzh->lock);
#endif
			return false;
		}

	lz_hashmap_put(p_lzh->map, p_lzh->capa, lz_hashmap_func, k, v);
	p_lzh->size++;
	
#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_post(&p_lzh->lock);
#endif

	return true;
}


lz_value lz_hashmap_get(_lz_hashmap* p_lzh, lz_key k)
{
#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_wait(&p_lzh->lock);
#endif

	static uint32_t hash;	
	hash = lz_hashmap_func(k) % p_lzh->capa;
	
	int t = hash;
	
	while(p_lzh->map[hash].v != NULL){
		if(lz_hashmap_equal(k, p_lzh->map[hash].k)){
#ifdef LZ_HASHMAP_THREAD_SAFE
			sem_post(&p_lzh->lock);
#endif
			return p_lzh->map[hash].v;
		}
		hash = (hash + 1) % p_lzh->capa;
	}
	

#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_post(&p_lzh->lock);
#endif
	
	return NULL;
}


int lz_hashmap_get_pos(_lz_hashmap* p_lzh, lz_key k)
{
#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_wait(&p_lzh->lock);
#endif
	static uint32_t hash;	
	hash = lz_hashmap_func(k) % p_lzh->capa;
	int t = hash;
	
	while(p_lzh->map[hash].v != NULL){
		if(lz_hashmap_equal(k, p_lzh->map[hash].k)){
#ifdef LZ_HASHMAP_THREAD_SAFE
			sem_post(&p_lzh->lock);
#endif
			return hash;
		}
		hash = (hash + 1) % p_lzh->capa;
	}

#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_post(&p_lzh->lock);
#endif
	return -1;
}


void lz_hashmap_cleanup(_lz_hashmap* p_lzh)
{
/* no ownership */
#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_wait(&p_lzh->lock);
#endif

	int i = 0;
	for(i = 0; i < p_lzh->capa; i++)
		if(p_lzh->map[i].k != NULL){	
#ifdef LZ_HASHMAP_THREAD_SAFE
			sem_post(&p_lzh->lock);
#endif	
			exit(EXIT_FAILURE);
		}
		
	free(p_lzh->map);
	
#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_post(&p_lzh->lock);
#endif
}


bool lz_hashmap_remove(_lz_hashmap* p_lzh, lz_key k, _lz_pair* lp)
{
	int i;
	int pos = lz_hashmap_get_pos(p_lzh, k);
	
	if(pos < 0)
		return false;

	_lz_pair* tmp = (_lz_pair*)malloc(sizeof(_lz_pair) * p_lzh->capa);
	memset(tmp, 0x00, (sizeof(_lz_pair) * p_lzh->capa));
	if(tmp == NULL)
		return false;
	
#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_wait(&p_lzh->lock);
#endif
	
	if(pos != -1){
		lp->k = p_lzh->map[pos].k;
		lp->v = p_lzh->map[pos].v;
		p_lzh->map[pos].k = NULL;
		p_lzh->map[pos].v = NULL;
	}
	
	lz_hashmap_rearrange_x(p_lzh, tmp);
	
	free(p_lzh->map);
	p_lzh->map = tmp;

#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_post(&p_lzh->lock);
#endif

	return true;
}


bool lz_hashmap_remove_x(_lz_hashmap* p_lzh, lz_key k)
{
	int i;
	int pos = lz_hashmap_get_pos(p_lzh, k);
	if(pos < 0)
		return false;

	_lz_pair* tmp = (_lz_pair*)malloc(sizeof(_lz_pair) * p_lzh->capa);
	memset(tmp, 0x00, (sizeof(_lz_pair) * p_lzh->capa));
	if(tmp == NULL)
		return false;
	
#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_wait(&p_lzh->lock);
#endif
	
	if(pos != -1){
		p_lzh->map[pos].k = NULL;
		p_lzh->map[pos].v = NULL;
	}
	
	lz_hashmap_rearrange_x(p_lzh, tmp);
	
	free(p_lzh->map);
	p_lzh->map = tmp;

#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_post(&p_lzh->lock);
#endif

	return true;
}


char* lz_hashmap_to_string(_lz_hashmap* p_lzh, char* str)
{

#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_wait(&p_lzh->lock);
#endif

	static uint32_t i;
	char buf[128];
	
	for(i = 0; i < p_lzh->capa; i++){
		if(p_lzh->map[i].v != NULL){
			memset(buf, 0x00, 128);
			sprintf(buf, "[(%s, %s)]\n", p_lzh->map[i].k, p_lzh->map[i].v);
			strcat(str, buf);
		}
	}

#ifdef LZ_HASHMAP_THREAD_SAFE
	sem_post(&p_lzh->lock);
#endif

	return str;
}


_lz_hashmap* new_lz_hashmap()
{
	_lz_hashmap* p_lzh = NULL;
	p_lzh = (_lz_hashmap*)malloc(sizeof(_lz_hashmap));
	if(p_lzh){
		p_lzh->pthis = &lz_hashmap_method_tbl;
		lz_hashmap_initialize(p_lzh);
		return p_lzh;		
	}
	else{
		exit(EXIT_FAILURE);
	}
}


_lz_hashmap* new_lz_hashmap_x(int sz)
{
	_lz_hashmap* p_lzh = NULL;
	p_lzh = (_lz_hashmap*)malloc(sizeof(_lz_hashmap));
	if(p_lzh){
		p_lzh->pthis = &lz_hashmap_method_tbl;
		lz_hashmap_initialize_x(p_lzh, sz);
	}
	
	return p_lzh;
}


void delete_lz_hashmap(_lz_hashmap* p_lzh)
{
	if(p_lzh){
		lz_hashmap_cleanup(p_lzh);
		free(p_lzh);
	}
}
