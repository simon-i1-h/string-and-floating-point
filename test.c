#include "string_and_floating_point.h"
#include <stdio.h>

int
main(void)
{
	double receive;
	char *str;

	/* キリがいい */

	str = "0.5";
	string_to_double(str, &receive);
	printf("str: %s, double: %f\n", str, receive);

	str = "1.0";
	string_to_double(str, &receive);
	printf("str: %s, double: %f\n", str, receive);

	str = "12.625";
	string_to_double(str, &receive);
	printf("str: %s, double: %f\n", str, receive);

	/* キリが悪い */

	str = "0.1";
	string_to_double(str, &receive);
	printf("str: %s, double: %f\n", str, receive);

	return 0;
}
