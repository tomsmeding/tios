#include <stdlib.h>
#include "dialog.h"

// allocates enough memory for and creates a new Dialog.
struct Dialog *newDialog(void) {
	struct Dialog *res = malloc(sizeof(struct Dialog));
	res->nitems = 0;
	return res;
}

// adds the given DialogItem item to the given Dialog
void addItem(struct Dialog *d, struct DialogItem *item) {
	d->items[d->nitems] = item;
	d->nitems++;
}

// frees all resources currently allocated for the given Dialog.
void destroyDialog(struct Dialog *d) {
	int i;
	for (i = 0; i < d->nitems; i++) {
		free(d->items[i]);
	}
	free(d);
}
