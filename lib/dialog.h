#ifndef __DIALOG__
#define __DIALOG__

enum DialogItemType {
	TEXT_NON_HL = 1,
	SELECT = 2,
	STRING_NUM = 3,
	TEXT_HL = 4,
	NUM_STRING = 5,
	HIDDEN = 6
};
struct DialogItem {
	enum DialogItemType type;
	int numChoices;
};

struct Dialog {
	int nitems;
	struct DialogItem *items[10];
};

struct Dialog *newDialog(void);
void addItem(struct Dialog *d, struct DialogItem *item);
void destroyDialog(struct Dialog *d);

#endif
