#include "string_and_floating_point.h"
#include <stdio.h>

int
main(void)
{
	double receive;
	char *str;

	/* キリがいい */

	str = "0.5";
	strint_to_double(str, &receive);
	printf("str: %s, double: %lf\n", str, receive);

	str = "1.0";
	strint_to_double(str, &receive);
	printf("str: %s, double: %lf\n", str, receive);

	str = "12.625";
	strint_to_double(str, &receive);
	printf("str: %s, double: %lf\n", str, receive);

	/* キリが悪い */

	str = "0.1";
	strint_to_double(str, &receive);
	printf("str: %s, double: %lf\n", str, receive);

	return 0;
}
