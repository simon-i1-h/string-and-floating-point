#include <string.h>

int
string_to_double(const char *src, double *dst)
{
	size_t len = strlen(src);
	enum state {
		STATE_INIT,
		STATE_ZERO,
		STATE_INTEGER,
		STATE_DOT,
		STATE_FRACTION
	} st = STATE_INIT;
	double exp = 0.1;

	*dst = 0.0;

	for (size_t i = 0; i < len; i++) {
		char c = src[i];

		switch (st) {
		case STATE_INIT: {
			if (c == '0') {
				st = STATE_ZERO;
				break;
			} else if (c >= '1' && c <= '9') {
				*dst = c - '0';
				st = STATE_INTEGER;
				break;
			}

			/* unexpected character */
			return -1;
		}
		case STATE_ZERO: {
			if (c == '.') {
				st = STATE_DOT;
				break;
			}

			/* unexpected character */
			return -1;
		}
		case STATE_INTEGER: {
			if (c == '.') {
				st = STATE_DOT;
				break;
			} else if (c >= '0' && c <= '9') {
				*dst *= 10;
				*dst += c - '0';
				break;
			}

			/* unexpected character */
			return -1;
		}
		case STATE_DOT: {
			st = STATE_FRACTION;
			__attribute__((fallthrough));
		}
		case STATE_FRACTION: {
			if (c >= '0' && c <= '9') {
				*dst += (c - '0') * exp;
				exp *= 0.1;
				break;
			}

			/* unexpected character */
			return -1;
		}
		}
	}

	return 0;
}
