#include <stdio.h>
#include <stdlib.h>
#include "lz_typeconv.h"


int main(void)
{
    char *buf = "27.41442TEST";
    char buf2[20];

    // lz_str_2_int
    printf("%d\n", lz_str_2_int(buf, strlen(buf)));

    // lz_str_2_long
    printf("%ld\n", lz_str_2_long(buf, strlen(buf)));

    // lz_str_2_llong
    printf("%lld\n", lz_str_2_llong(buf, strlen(buf)));

    // lz_str_2_float
    printf("%f\n", lz_str_2_float(buf, strlen(buf)));

    // lz_str_2_float_decimal
    printf("%f\n", lz_str_2_float_decimal(buf, strlen(buf), 3));

    // lz_str_2_double
    printf("%f\n", lz_str_2_double(buf, strlen(buf)));

    // lz_str_2_float_decimal
    printf("%f\n", lz_str_2_double_decimal(buf, strlen(buf), 1));

    // lz_int_2_leading_zero_str
    lz_int_2_leading_zero_str(buf2, 5, 727);
    printf("%s\n", buf2);

    return 0;
}
