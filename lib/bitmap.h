#ifndef __BITMAP__
#define __BITMAP__

#include <stdint.h>
#include <stdbool.h>

inline void clearBitmap(uint8_t*, unsigned int);
inline bool getBit(uint8_t*, unsigned int);
inline void setBit(uint8_t*, unsigned int, bool);

#endif
