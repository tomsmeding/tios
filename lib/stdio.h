#ifndef __STDIO__
#define __STDIO__

#include "stdlib.h"

#define KEY_OFF 0x3F

#define CUR_MAX_WIDTH 15
#define CUR_MAX_HEIGHT 7
__at 0x844B unsigned int CurRow;
__at 0x844C unsigned int CurCol;
uint8_t moveCur(uint8_t x, uint8_t y);

uint8_t getKey();
uint8_t getKeyNonBlock();
/*
inline void alphaAlpha();
char getchar();
*/

enum TextMode {
	TM_BIG,
	TM_SMALL
};
extern enum TextMode textMode;
void putchar(char c);
#include <stdio.h>

#define PEN_MAX_WIDTH 63
#define PEN_MAX_HEIGHT 95
__at 0x86D7 unsigned int PenCol;
__at 0x86D8 unsigned int PenRow;
uint8_t movePen(uint8_t x, uint8_t y);

void showLoadIndicator(bool show);

// TODO: better name for this
void clearLcd();

void printNumber(int number);

/*
void print(char *s) __naked;
void puts(char *s);
*/

/*
int scanf(char *fmt, ...);
*/

void setCursor(bool on);
char keypadScancodeToChar(uint8_t keycode);
char getDigitNonBlock(void);
char getDigit(void);
char *askNumber(char *s, int maxstrlen);

#endif
