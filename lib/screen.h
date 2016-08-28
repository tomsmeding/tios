#ifndef __SCREEN__
#define __SCREEN__

#include <stdint.h>
#include <stdbool.h>

extern const uint8_t screenWidth;
extern const uint8_t screenHeight;
extern const uint16_t screenSize; // screenWidth * screenHeight

// == basic
extern uint8_t * const screen;
__sfr __at 0x10 LcdCommandPort;
__sfr __at 0x11 LcdDataPort;

bool getPixel(uint8_t x, uint8_t y);
void setPixel(uint8_t x, uint8_t y, bool val);

void redrawScreen(void);

void clearScreen(bool redraw);

void cpyBitmapToDispBuf(uint8_t map[]);
void cpyArrToDispBuf(bool buf[]);

// == advanced

inline void lcdDelay(void);
inline void _sendLcdCommand(uint8_t command);

typedef enum {
	X_DEC = 0x04,
	X_INC = 0x05,
	Y_DEC = 0x06,
	Y_INC = 0x07
} LcdAutoMoveMode;

uint8_t setCol(uint8_t col);
uint8_t setRow(uint8_t row);

void setAutoMoveMode(LcdAutoMoveMode mode);

void diffRedraw(uint8_t newScreen[]) __critical;

void resetScreen(void);

#endif
