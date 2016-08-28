#include "stdio.h"

#include "bitmap.h"

uint8_t moveCur(uint8_t x, uint8_t y) {
	if (x > CUR_MAX_WIDTH || y > CUR_MAX_HEIGHT) {
		return 1;
	}
	CurCol = x;
	CurRow = y;

	return 0;
}

uint8_t getKey() __naked {
	__asm
		push ix
		rst #0x28
		.dw #0x500B
		ld l, a
		pop ix
		ret
	__endasm;
}
uint8_t getKeyNonBlock() __naked {
	__asm
		push ix
		rst #0x28
		.dw #0x4018
		ld l, a
		pop ix
		ret
	__endasm;
}
/*
inline void alphaAlpha() {
	__asm
		set LwrCaseActive,(IY+AppLwrCaseFlag)
	__endasm;
}
char getchar() {
	char key;
	alphaAlpha();

	key = getKey();
	if (key == 0x05) { // [enter]
		return '\n';
	} else if (key == 0x0A) { // [del]
		return '\b';
	} else {
		return key - 0xE2 + 'a';
	}
}
*/

enum TextMode textMode = TM_BIG;
static void _newline() __naked {
	__asm
		rst #0x28
		.dw #0x452E
		ret
	__endasm;
}
static void _VPutMap(char c) {
	c;
	__asm
		ld a, 4(ix)
		rst #0x28
		.dw #0x455E
	__endasm;
}
static void _putC(char c) {
	c;
	__asm
		ld a, 4(ix)
		rst #0x28
		.dw #0x4504
	__endasm;
}
void putchar(char c) {
	// TODO: CurCol and PenCol underflow guards

	if (textMode == TM_BIG) {
		if (c == '\n') {
			_newline();
		} else if (c == '\b') {
			CurCol--;
		} else {
			_putC(c);
		}
	} else if (textMode == TM_SMALL) {
		if (c == '\n') {
			PenCol = 0;
			PenRow++;
		} else if (c == '\b') {
			PenCol--;
		} else {
			_VPutMap(c);
		}
	}
}

uint8_t movePen(uint8_t x, uint8_t y) {
	if (x > PEN_MAX_WIDTH || y > PEN_MAX_HEIGHT) {
		return 1;
	}
	PenCol = x;
	PenRow = y;

	return 0;
}

void showLoadIndicator(bool show) {
	show;
	__asm
		ld a, 4(ix)
		or a
		jr z, load_off

		load_on:
			rst #0x28
			.dw #0x456D
			ret
		load_off:
			rst #0x28
			.dw #0x4570
	__endasm;
}

// TODO: better name for this
void clearLcd() __naked {
	__asm
		push ix
		rst #0x28
		.dw #0x4558 // _HomeUp
		rst #0x28
		.dw #0x4540 // _ClrLCDFull
		pop ix
		ret
	__endasm;
}

void printNumber(int number) {
	number;
	__asm
		ld l, 4(ix)
		ld h, 5(ix)
		rst #0x28
		.dw #0x4507
	__endasm;
}

/*
void print(char *s) __naked {
	s;
	__asm
		ld l,4(ix)
		ld h,5(ix)
		rst #0x28
		.dw #0x450A
		ret
	__endasm;
}

void puts(char *s) {
	print(s);
	_newline();
}
*/

/*
int scanf(char *fmt, ...) {
	bool ignore = false;
	uint width = 0;
	va_list ap;
	va_start(ap, fmt);

	if (*fmt != '%') {
		return -1;
	}
	fmt++;

	if (*fmt == '*') {
		ignore = true;
		fmt++;
	}

	while (isdigit(*fmt)) {
		width = (width * 10) + (*fmt - '0');
		fmt++;
	}

	switch(*fmt) {
	case 'i': {
		int *i = va_arg(ap, *int);
		(*i) = 
			break;
	}
	}
}
*/

void setCursor(bool on) __naked {
	on;
	__asm
		push ix
		ld a, 4(ix)

		or a
		jr z, cur_off

		cur_on:
			rst #0x28
			.dw #0x45C4
		cur_off:
			rst #0x28
			.dw #0x45BE

		pop ix
		ret
	__endasm;
}
char keypadScancodeToChar(uint8_t keycode) {
	switch (keycode) {
	case 0x12: return '3';
	case 0x13: return '6';
	case 0x14: return '9';
	case 0x21: return '0';
	case 0x1A: return '2';
	case 0x1B: return '5';
	case 0x1C: return '8';
	case 0x22: return '1';
	case 0x23: return '4';
	case 0x24: return '7';
	default:   return 0;
	}
}
char getDigitNonBlock(void) {
	return keypadScancodeToChar(getKeyNonBlock());
}
char getDigit(void) {
	while (true) {
		char c = getDigitNonBlock();
		if (c) return c;
	}
}
char *askNumber(char *s, int maxstrlen) {
	char *buf = malloc((maxstrlen+1) * sizeof(char));
	register uint8_t i = 0;

	if (s != NULL && strlen(s) > 0) {
		printf("%s: ", s);
	}

	setCursor(true);

	while (true) {
		uint8_t key = getKeyNonBlock();

		if (key == 0x0) { // nothing
			continue;
		} else if (key == 0x9) { // enter
			break;
		} else if (i > 0 && key == 0x38) { // del
			i--;
			buf[i] = '\0';
			CurCol--;
			_putC(' ');
			CurCol--;
		} else if (i > 0 && key == 0x0F) { // clear
			while (i-->0) {
				buf[i] = '\0';
				CurCol--;
				_putC(' ');
				CurCol--;
			}
			i = 0;
		} else if (i-(buf[0] == '-' ? 1 : 0) != maxstrlen) {
			char c = 0;

			if (i == 0 && key == 0x11) { // minus
				c = '-';
			} else { // numbers
				c = keypadScancodeToChar(key);
			}

			if (c) {
				buf[i] = c;
				_putC(c);
				i++;
			}
		}
	}

	setCursor(false);
	_newline();
	return buf;
}
