#include "lib/stdio.h"

int main(void) {
	char *num = askNumber("", 5);

	int i = atoi(num);
	printf("%d\n", i);

	free(num);
	return 0;
}

/*
#include "lib/stdio.h"
#include "lib/screen.h"

#define GSC_LEFT 2
#define GSC_RIGHT 3
#define GSC_CLEAR 15

#define METEORITE_COUNT 10

const uint8_t maxX = 86;
const uint8_t meteorHeight = 10;

struct Meteorite {
	int x;
	int y;
};
struct Meteorite *createMeteorite(void) {
	struct Meteorite *m = malloc(sizeof(struct Meteorite));

	m->x = rand() * screenWidth / RAND_MAX;
	m->y = 0 - meteorHeight;

	return m;
}

struct State {
	uint8_t x;
	struct Meteorite *meteorites[METEORITE_COUNT];
};
struct State *createState(void) {
	struct State *state = malloc(sizeof(struct State));
	int i;
	for (i = 0; i < METEORITE_COUNT; i++) {
		state->meteorites[i] = createMeteorite();
	}
	return state;
}

bool handleInput(struct State *self) {
	uint8_t keycode = getKeyNonBlock();
	if (keycode == GSC_LEFT && self->x != 0) {
		puts("<-");
		self->x--;
	} else if (keycode == GSC_RIGHT && self->x + 1 != maxX) {
		puts("->");
		self->x++;
	} else if (keycode == GSC_CLEAR) {
		return false;
	} else {
		puts("");
	}
	return true;
}

void moveMeteorites(struct State *state) {
	int i;
	for (i = 0; i < METEORITE_COUNT; i++) {
		struct Meteorite *m = state->meteorites[i];
		if (m == NULL) continue;
	}
}

void replaceMeteorites(struct State *state) {
	int i;
	for (i = 0; i < METEORITE_COUNT; i++) {
		struct Meteorite *m = state->meteorites[i];
		if (m->y >= screenHeight) {
			free(m);
			state->meteorites[i] = createMeteorite();
		}
	}
}

bool collDetect(struct State *state) {
	int i;
	for (i = 0; i < METEORITE_COUNT; i++) {
		struct Meteorite *m = state->meteorites[i];
		if (m) { // TODO: coll detect
		}
	}
	return false;
}

void renderState(struct State *state) {
	int i;
	clearScreen(false);
	for (i = 0; i < METEORITE_COUNT; i++) {
		struct Meteorite *m = state->meteorites[i];
		// TODO: render meteorite
	}
	// TODO: render player
	redrawScreen();
}

void freeState(struct State *state) {
	int i;
	for (i = 0; i < METEORITE_COUNT; i++) {
		free(state->meteorites[i]);
	}
	free(state);
}

int main(void) {
	struct State *state = createState();
	clearScreen(true);
	srand(getRefreshCount());

	while (true) {
		// double press [clear] to exit
		if (!handleInput(state)) {
			clearScreen(true);
			moveCur(0, 0);
			puts("sure?");
			if (getKey() == 0x09) break;
		}

		moveMeteorites(state);
		replaceMeteorites(state);

		if (collDetect(state)) {
			clearScreen(true);
			moveCur(0, 0);
			puts("ur ded noob");
		}

		renderState(state);
	}

	freeState(state);
	clearScreen(true);
	clearLcd();
	return 0;
}
*/
