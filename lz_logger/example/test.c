#include <stdio.h>
#include "lz_logger.h"

int main(void)
{
	lz_log(".", "testlog", __FILE__, __LINE__, "wassup there %d", 727);
	return 0;
}
