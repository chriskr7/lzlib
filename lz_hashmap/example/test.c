#include <stdio.h>
#include <memory.h>
#include "lz_hashmap.h"

#define TEST_CNT 5

static const char test_set[TEST_CNT][16][16]={
	{"one", "chris"},
	{"two", "miro"},
	{"three", "woonmook"},
	{"four", "minwoo"},
	{"five", "sangsoo"}
};

int main(void)
{
	/*
	*	dynamic allocation 방법 (using malloc)
	*	default init : lz_new_hashmap() - hashmap 크기 : default(4098)
	*   size init: lz_new_hashmap_x(int sz) - hashmap 크기 : sz
	*/

	_lz_hashmap* p_lzh = new_lz_hashmap();
	int i;
	char buf[1024];

	/* 입력 (key, value) */
	for(i = 0; i < TEST_CNT; i++)
		if(p_lzh->pthis->set(p_lzh, (lz_key)test_set[i][0], (lz_value)test_set[i][1]) != true){
			printf("set failed! key: %s\n", test_set[i][0]);
		}

	/* key값에 대한 value get */
	lz_key k = (lz_key)"one";
    printf("%s\n", (char*)k);
	printf("%s\n", (char*)p_lzh->pthis->get(p_lzh, k));

	/* hashmap to_string */
	printf("%s\n", p_lzh->pthis->to_string(p_lzh, buf));


	/* 제거 remove 		: pair를 얻고 제거
	        remove_x	: 그냥 제거							*/
	_lz_pair lp;
	for(i = 0; i < TEST_CNT; i++){
		if(!p_lzh->pthis->remove(p_lzh, (lz_key)test_set[i][0], &lp))
			printf("fail to remove [%s]\n", (lz_key)test_set[i][0]);
		else
			printf("removing: [%s\t%s]\n", lp.k, lp.v);
	}

	/* delete hashmap */
	delete_lz_hashmap(p_lzh);


	printf("------------------------------------------------\n");

	/*
	*	static allocation 방법
	*/
	_lz_hashmap lzh;
	memset(buf, 0x00, 1024);

	/*
	*	default init : lz_hashmap_init(_lz_hashmap*) - hashmap 크기 : default(4098)
	*   size init: lz_hashmap_init(_lz_hashmap*, int sz) - hashmap 크기 : sz
	*/
	lz_hashmap_init(&lzh);

	/* 입력 (key, value) */
	for(i = 0; i < TEST_CNT; i++)
		lzh.pthis->set(&lzh, (lz_key)test_set[i][0], (lz_value)test_set[i][1]);

	/* key값에 대한 value get */
	lz_key k2 = (lz_key)"three";
	printf("%s\n", (char*)lzh.pthis->get(&lzh, k2));

	/* hashmap to_string */
	printf("%s\n", lzh.pthis->to_string(&lzh, buf));

	/* 제거 remove 		: pair를 얻고 제거
	        remove_x	: 그냥 제거							*/
	for(i = 0; i < TEST_CNT; i++){
		lzh.pthis->remove_x(&lzh, (lz_key)test_set[i][0]);
	}

	/* no delete static allocation */

	return 0;
}
