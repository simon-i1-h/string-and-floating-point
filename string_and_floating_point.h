#ifndef STRING_AND_FLOATING_POINT_H
#define STRING_AND_FLOATING_POINT_H

#include <stddef.h>

/*
 * 文法(正規表現？): (0|[1-9][0-9]*)\.[0-9]+
 * return: -1 (error) or 0 (succeeded)
 */
int string_to_double(const char *src, double *dst);

/*
 * snprintfに似たAPI。sizeはdstの終端文字分を含む大きさで、返り値は終
 * 端文字を除いた文字列としての長さ。
 */
int double_to_string(char *dst, size_t size, double src);

/* asprintfに似たAPI。 */
int alloc_double_to_string(char **dst, double src);

#endif /* STRING_AND_FLOATING_POINT_H */
