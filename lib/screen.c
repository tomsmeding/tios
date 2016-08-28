#include "screen.h"
#include "bitmap.h"

const uint8_t screenWidth = 96;
const uint8_t screenHeight = 64;
const uint16_t screenSize = 6144; // screenWidth * screenHeight

uint8_t * const screen = 0x9340;

// == basic
bool getPixel (uint8_t x, uint8_t y) {
	if (x >= screenWidth || y >= screenHeight) {
		return false;
	}
	return getBit(screen, screenWidth*y + x);
}
void setPixel(uint8_t x, uint8_t y, bool val) {
	if (x < screenWidth && y < screenHeight)
		setBit(screen, screenWidth*y + x, val);
}
/*
void setPixel(uint8_t x, uint8_t y, bool val) __naked {
	x; y; val;
	__asm
		push ix
		ld ix, #0x0
		add ix, sp
		ld a, 4(ix)
		ld d, a
		ld a, 5(ix)
		ld e, a
		ld a, 6(ix)
		push bc
		push de
		push hl
		push af
		ld b, a  // b=boolval
		ld a, e
		sla a
		add a, e
		ld l, a
		ld h, #0x0
		add hl, hl
		add hl, hl  // hl=12*y
		ld e, d  // e=x
		ld a, d
		and #0x07  // a=x%8
		srl e
		srl e
		srl e  // e=x/8
		ld d, #0x0
		add hl, de  // hl=12*y+x/8
		ld de, #0x9340
		add hl, de  // hl=address of byte
		ex de, hl
		ld hl, #pa_bitshifts
		add a, l
		ld l, a
		ld a, h
		adc a, #0x0
		ld h, a
		ld a, (hl)
		ld c, a  // c=bitshift
		ex de, hl
		ld a, b
		or a
		jr z, pa_resetbit
	pa_setbit:
		ld a, (hl)
		or c
		ld (hl), a
		jr pa_epilogue
	pa_resetbit:
		ld a, c
		cpl
		ld c, a
		ld a, (hl)
		and c
		ld (hl), a
	pa_epilogue:
		pop af
		pop hl
		pop de
		pop bc
		pop ix
		ret
	pa_bitshifts:
		.db #0x80, #0x40, #0x20, #0x10, #0x08, #0x04, #0x02, #0x01
	__endasm;
}
*/

void redrawScreen(void) __naked {
	__asm
		di
		ld a,#0x80
		out (#0x10),a
		ld hl,#0x9340-12-(-(12*64)+1)
		ld a,#0x20
		ld c,a
		inc hl
		dec hl
	fastCopyAgain:
		ld b,#0x40
		inc c
		ld de, #-0x2ff // -(12*64)+1
		out (#0x10),a
		add hl,de
		ld de,#0xa
	fastCopyLoop:
		add hl,de
		inc hl
		inc hl
		inc de
		ld a,(hl)
		out (#0x11),a
		dec de
		djnz fastCopyLoop
		ld a,c
		cp #0x2B+1
		jr nz, fastCopyAgain
		ei
		ret
	__endasm;
}

void clearScreen(bool redraw) {
	clearBitmap(screen, screenSize);
	if (redraw) redrawScreen();
}

void cpyBitmapToDispBuf(uint8_t map[]) {
	int i = screenSize / 8;
	while (i-->0) {
		screen[i] = map[i];
	}
}

void cpyArrToDispBuf(bool buf[]) {
	int i = screenSize;
	while(i-->0) {
		setBit(screen, i, buf[i]);
	}
}

// == advanced

inline void lcdDelay(void) {
	__asm
		nop
		nop
		nop
		nop
		nop
		nop
	__endasm;
}

// sends a command to the LCD driver and waits enough time for the LCD driver to
// process it.
inline void _sendLcdCommand(uint8_t command) {
	LcdCommandPort = command;
	lcdDelay();
}

uint8_t setCol(uint8_t col) {
	if (col >= screenWidth) {
		return 1;
	}
	_sendLcdCommand(col + 0x20);
	return 0;
}
uint8_t setRow(uint8_t row) {
	if (row >= screenHeight) {
		return 1;
	}
	_sendLcdCommand(row + 0x80);
	return 0;
}

void setAutoMoveMode(LcdAutoMoveMode mode) {
	_sendLcdCommand(mode);
}

void diffRedraw(uint8_t newScreen[]) __critical {
	int i;
	bool next = false;
	for (i = 0; i < screenSize / 8; i++) {
		uint8_t newByte = newScreen[i];
		// just skip this byte when it hasn't changed
		if (screen[i] == newByte) {
			next = false;
			continue;
		} else {
			if (!next) {
				int y = i / (screenWidth / 8);
				int x = i % (screenWidth / 8);
				_sendLcdCommand(y + 0x80);
				_sendLcdCommand(x + 0x20);
			}

			LcdDataPort = newByte;
			screen[i] = newByte;
			next = true;
		}
	}
}

// Resets the screen to make sure it's ready to go for TI-OS.
void resetScreen(void) {
	setAutoMoveMode(X_INC);
	clearScreen(true);
}
