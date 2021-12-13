#ifndef PLAYER
#define PLAYER
typedef struct Player {
	void *self;
	linkedList *controls;
	//Anim *sprite;
	int num;
	Joypad *joy;
} Player;
#include "PlayerManager.h"
#include "poopPlayer.h"

Player *makePlayer(void *character, /*Anim *sprite,*/ int num);
void addControl(Player *player, char *inp, void (*n_func)(void*,float));
void freePlayer(Player *p);

#endif
