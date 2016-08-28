#include "bitmap.h"

#define BITS_PER_BYTE 8
#define BYTE_OFFSET(b) ((b) / BITS_PER_BYTE)
#define BIT_OFFSET(b)  ((b) % BITS_PER_BYTE)
static const uint8_t bittable[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };

inline void clearBitmap(uint8_t *map, unsigned int n) {
	int i = n / BITS_PER_BYTE;
	while (i-->0) {
		map[i] = (uint8_t) 0;
	}
}

inline bool getBit(uint8_t *map, unsigned int n) {
	return map[BYTE_OFFSET(n)] & bittable[BIT_OFFSET(n)];
}

inline void setBit(uint8_t *map, unsigned int n, bool val) {
	if (val) {
		map[BYTE_OFFSET(n)] |= bittable[BIT_OFFSET(n)];
	} else {
		map[BYTE_OFFSET(n)] &= ~bittable[BIT_OFFSET(n)];
	}
}

#undef BITS_PER_BYTE
#undef BYTE_OFFSET
#undef BIT_OFFSET
