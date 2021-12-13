#include "Player.h"
#include "PlayerManager.c"
#include "poopPlayer.c"

Player *makePlayer(void *character, /*Anim *sprite, */int num) {
	Player *p = (Player *)calloc(1, sizeof(Player));
	p->num = num;
	p->self = character;
	//p->sprite = sprite;
	p->controls = makeList();
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
	free(p);
}
