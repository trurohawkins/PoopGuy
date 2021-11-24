#include "Player.h"

Player *makePlayer(Actor *character, Anim *sprite) {
	Player *p = (Player *)calloc(1, sizeof(Player));
	p->self = character;
	p->sprite = sprite;
	p->controls = makeList();
	return p;
}

void addControl(Player *player, char *inp, void (*n_func)(float)) {
	InpMap *im = (InpMap*)calloc(1, sizeof(InpMap));
	im->input = inp;
	im->func = n_func;
	addToList(&(player->controls),im);
}

void processKeys(Player *p) {
	linkedList *cur = getCurInput();
	if (cur != NULL && cur->data != NULL) {
		while (cur != NULL) {
			inpReceived *ir = (inpReceived*)cur->data;
			char *inp = ir->input;
			linkedList *con = p->controls;
			while (con != NULL) {
				InpMap *tmp = (InpMap*)con->data;
				char *c = tmp->input;
				if (strCompare(inp, c) == true) {
					tmp->func(ir->val);
					break;
				} 
				con = con->next;
			}
			cur = cur->next;
		}
	}
	clearInput();
}

void freePlayer(Player *p) {
	freeList(&p->controls);
	free(p);
}
