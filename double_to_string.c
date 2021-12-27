#include "string_and_floating_point.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#define countof(arr) (sizeof(arr) / sizeof((arr)[0]))

inline static void
copyc(int retlen, char *dst, size_t size, char c)
{
	if ((unsigned int)retlen + 1 < size) {
		dst[retlen] = c;
	} else if ((unsigned int)retlen + 1 == size) {
		dst[retlen] = '\0';
	} else /* retlen + 1 > size */ {
		/* no-op */
	}
}

inline static int
double_to_string_integer(int retlen, char *dst, size_t size, double integer)
{
	char str[CHAR_BIT * sizeof(double)];
	int index = countof(str);

	str[--index] = '\0';
	if (integer == 0) {
		str[--index] = '0';
	} else {
		while (integer != 0) {
			double d = fmod(integer, 10);
			str[--index] = (int)d + '0';
			(void)modf(integer / 10, &integer);
		}
	}

	for (int i = index; str[i] != '\0'; i++, retlen++)
		copyc(retlen, dst, size, str[i]);

	return retlen;
}

inline static int
double_to_string_fraction(int retlen, char *dst, size_t size, double fraction)
{
	char str[CHAR_BIT * sizeof(double)];
	int index = 0;

	if (fraction == 0) {
		str[index++] = '0';
	} else {
		while (fraction != 0) {
			double d;
			fraction = modf(fraction * 10, &d);
			str[index++] = (int)d + '0';
		}
	}
	str[index++] = '\0';

	for (int i = 0; str[i] != '\0'; i++, retlen++)
		copyc(retlen, dst, size, str[i]);

	return retlen;
}

int
double_to_string(char *dst, size_t size, double src)
{
	int retlen = 0;
	double integer, fraction;
	fraction = modf(src, &integer);

	retlen = double_to_string_integer(retlen, dst, size, integer);
	copyc(retlen++, dst, size, '.');
	retlen = double_to_string_fraction(retlen, dst, size, fraction);

	if ((unsigned int)retlen + 1 <= size)
		dst[retlen] = '\0';

	return retlen;
}

int
alloc_double_to_string(char **dst, double src)
{
	int retlen = double_to_string(NULL, 0, src);
	if (retlen < 0)
		return -1;
	*dst = malloc(retlen + 1);
	if (*dst == NULL)
		return -1;
	retlen = double_to_string(*dst, retlen + 1, src);
	if (retlen < 0) {
		free(*dst);
		return -1;
	}
	return retlen;
}
