#include "stdlib.h"

void itoa(int i, char *str) {
	_itoa(i, str, 10);
}

/*
int atoi(const char *s) {
	int res = 0;
	while (*s != '\0') {
		res *= 10;
		res += (*s - '0');
		s++;
	}
	return res;
}

void itoa(int i, char buf[]) {
	char *b = buf;
	char c;

	// insert sign
	if (i < 0) {
		*buf = '-';
		buf++;
		i *= -1;
	}

	do {
		*b = i%10 + '0';
		b++;
		i /= 10;
	} while (i);
	*b=0;

	b--;
	while(buf<b){
		c=*buf;
		*buf=*b;
		*b=c;
		buf++;
		b--;
	}
}
*/

inline void halt() {
	__asm
		halt
	__endasm;
}

/*
 * returns the content of the r register, which contains the count of opcodes
 * ran by the CPU since it has been turn on.
 * useful for pseudo RNG, for example:
 *
 *   int randomNumber;
 *   srand(getRefreshCount());
 *   randomNumber = rand();
 */
uint8_t getRefreshCount(void) __naked {
	__asm
		ld a, r
		ld l, a
		ret
	__endasm;
}

char *strdup(const char *s) {
	char *res = malloc(strlen(s) + 1);
	strcpy(res, s);
	return res;
}

char *strndup(const char *s, size_t n) {
	char *res = malloc(sizeof(char)*n + 1);
	strncpy(res, s, n);
	return res;
}
