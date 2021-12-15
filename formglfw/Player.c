#include "Player.h"
#include "PlayerManager.c"
#include "poopPlayer.c"

Player *makePlayer(void *character, int num, void (*deleteFunc)(void*)) {
	Player *p = (Player *)calloc(1, sizeof(Player));
	p->num = num;
	p->self = character;
	p->controls = makeList();
	p->delFunc = deleteFunc;
	addPlayer(p);
	return p;
}

void addControl(Player *player, char *inp, void (*n_func)(void*,float)) {
	InpMap *im = (InpMap*)calloc(1, sizeof(InpMap));
	im->input = inp;
	im->func = n_func;
	addToList(&(player->controls),im);
}


void freePlayer(Player *p) {
	freeList(&p->controls);
	if (p->delFunc != NULL) {
		p->delFunc(p->self);
	}
	free(p);
}
