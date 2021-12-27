#include "string_and_floating_point.h"
#include <stdio.h>
#include <stdlib.h>

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

	/* doubleをstringにする */

	double d;
	char buf[64];

	d = 42.0;
	double_to_string(buf, sizeof(buf), d);
	printf("double: %f, str: %s\n", d, buf);

	d = 0.75;
	double_to_string(buf, sizeof(buf), d);
	printf("double: %f, str: %s\n", d, buf);

	d = 42.75;
	double_to_string(buf, sizeof(buf), d);
	printf("double: %f, str: %s\n", d, buf);

	char *pbuf;
	d = 1000.75;
	alloc_double_to_string(&pbuf, d);
	printf("double: %f, str: %s\n", d, pbuf);
	free(pbuf);

	return 0;
}
