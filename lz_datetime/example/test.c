#include <stdio.h>
#include "lz_datetime.h"


int main(void)
{
	p_lz_date p_dt = new_lz_date();


	lz_datetime one, two;
	lz_datetime_init(&one);
	lz_datetime_init(&two);

	char buf[80];

	p_dt->pthis->get_localdate(p_dt);
	printf("today: %s\n", p_dt->pthis->to_string(p_dt, buf));

	delete_lz_date(p_dt);


	one.pthis->get_ldatetime(&one);

	convert_datetime(&one, "Asia/Seoul", &two, "UCT");

	printf("one: %s\n", one.pthis->to_string(&one, buf));
	printf("two: %s\n", two.pthis->to_string(&two, buf));

	lz_datetime cur;
	lz_datetime_init(&cur);
	cur.pthis->get_ldatetime(&cur);

	printf("cur: %s\n", cur.pthis->to_string(&cur, buf));


	return 0;
}
