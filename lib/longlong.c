#include "longlong.h"

long long atoll(const char *s) {
	long long res = 0;
	register char sign = 0;

	while (*s) {
		if ((*s <= '9' && *s >= '0') || *s == '-' || *s == '+') {
			break;
		}
		s++;
	}

	if (*s == '-' || *s == '+') {
		sign = (*s == '-');
		s++;
	}

	while (*s && *s >= '0' && *s <= '9') {
		res = (res * 10) + (*s - '0');
		s++;
	}

	return (sign ? -res : res);
}
