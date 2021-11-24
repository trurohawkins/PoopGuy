#ifndef PLAYER
#define PLAYER
#include "FormGlfw.h"

typedef struct Player {
	Actor *self;
	linkedList *controls;
	Anim *sprite;
	int num;
	Joypad *joy;
} Player;

Player *makePlayer(Actor *character, Anim *sprite);
void addControl(Player *player, char *inp, void (*n_func)(float));
void processKeys(Player *p);
void freePlayer(Player *p);

#endif
