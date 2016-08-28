#ifndef __STDLIB__
#define __STDLIB__

#include <stdint.h>
#include <stdbool.h>
#include "longlong.h"
typedef unsigned int uint;

#include <stdlib.h>
#include <string.h>

// TODO: remove this if it compiles
// extern int atoi(const char *);
void itoa(int i, char *str);

inline void halt();
uint8_t getRefreshCount(void);

char *strdup(const char *s);
char *strndup(const char *s, size_t n);

#endif
