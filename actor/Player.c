#include "Player.h"
Player *curPlayer;

Player *makePlayer (int sx, int sy) {
	Player *poopGuy = (Player *)calloc(1, sizeof(Player));
	poopGuy->speed = 10;
	poopGuy->maxForce = 10;
	poopGuy->me = makeActor(makeForm(0.2, 1, 0.2, sx, sy));
	poopGuy->me->body->id = 69;
	poopGuy->move = makeMove();
	Action *grav = makeGravity(poopGuy->move->vars);
	setFriction(grav, 10);
	poopGuy->jump = makeJump(poopGuy->move->vars, grav);
	poopGuy->eatPoop = makeStomach(poopGuy->me->body, sx, sy);
	poopGuy->control = makeControl();
	setPlayer(poopGuy->control->vars, poopGuy);
	addAction(poopGuy->me, poopGuy->move);
	addAction(poopGuy->me, grav);
	addAction(poopGuy->me, poopGuy->jump);
	addAction(poopGuy->me, poopGuy->eatPoop);
	addAction(poopGuy->me, poopGuy->control);
	//changeDir(poopGuy->eatPoop poopGuy->me->body, 3);
	//cv->moveRight = 1;
	curPlayer = poopGuy;
	return poopGuy;
}

Player *getPlayer() {
	return curPlayer;
}

void deletePlayer(Player *poopGuy) {
	eatPooVar *ep = (eatPooVar*)(poopGuy->eatPoop->vars);
	freeList(&(ep->stomach));
	free(poopGuy);
}

void keyPressPlayer(Player *poopGuy, char input) {
	eatPooVar *ep = (eatPooVar*)(poopGuy->eatPoop->vars);
	moveVar *mv = (moveVar*)poopGuy->move->vars;
	//printf("%c\n", input);
	controlVar *cv = (controlVar*)poopGuy->control->vars;
	switch (input) {
		case 65: //a
			changeDir(ep, poopGuy->me->body, 1);
			cv->moveLeft = 1;
			break;
		case 68: //d
			changeDir(ep, poopGuy->me->body, 3);
			cv->moveRight = 1;
			break;
		case 69:
			ep->eating = (ep->eating+1)%2;
			break;
		case 87://w
			changeDir(ep, poopGuy->me->body,0);
			break;
		case 83://s
			changeDir(ep, poopGuy->me->body,2);
			break;
		case 80:
			ep->pooping = 1;
			break;
		case 32:
			startJump(poopGuy->me->body, poopGuy->jump);
			break;
	}
	if (input == 97 || input == 100) {
		poopGuy->lastInp = input;
	}
}

void keyReleasePlayer(Player *poopGuy, char input) {
	eatPooVar *ep = (eatPooVar*)(poopGuy->eatPoop->vars);
	controlVar *cv = (controlVar*)poopGuy->control->vars;
	switch(input) {
		case 65:
			cv->moveLeft = 0;
			break;
		case 68:
			cv->moveRight = 0;
			break;
		case 80:
			ep->pooping = 0;
			break;
	}	
}

void up(float val) {
	if (val > 0) {
		eatPooVar *ep = (eatPooVar*)(curPlayer->eatPoop->vars);
		changeDir(ep, curPlayer->me->body,0);
	}
}

void left(float val) {
	controlVar *cv = (controlVar*)curPlayer->control->vars;
	eatPooVar *ep = (eatPooVar*)(curPlayer->eatPoop->vars);
	if (val > 0) {
		changeDir(ep, curPlayer->me->body, 1);
		cv->moveLeft = 1;
	} else {
		cv->moveLeft = 0;
	}
}

void right(float val) {
	controlVar *cv = (controlVar*)curPlayer->control->vars;
	eatPooVar *ep = (eatPooVar*)(curPlayer->eatPoop->vars);
	if (val > 0) {	
		changeDir(ep, curPlayer->me->body, 3);
		cv->moveRight = 1;
	} else {
		cv->moveRight = 0;
	}
}
void down(float val) {
	if (val > 0) {
		eatPooVar *ep = (eatPooVar*)(curPlayer->eatPoop->vars);
		changeDir(ep, curPlayer->me->body,2);
	}
}

void xMove(float val) {
	if (val > 0) {
		right(1);
	}  else if (val < 0) {
		left(1);
	} else {
		right(0);
		left(0);
	}
}
void yMove(float val) {
	if (val > 0) {
		up(1);
	}  else if (val < 0) {
		down(1);
	} else {
		up(0);
		down(0);
	}
}

void poop(float val) {
	eatPooVar *ep = (eatPooVar*)(curPlayer->eatPoop->vars);
	if (val > 0) {
		ep->pooping = 1;
	} else {
		ep->pooping = 0;
	}
}

void toggleEat(float val) {
	if (val > 0) {//only if when pressed not released
		eatPooVar *ep = (eatPooVar*)(curPlayer->eatPoop->vars);
		ep->eating = (ep->eating+1)%2;
	}
}

void jumpInp(float val) {
	if (val > 0) {
		startJump(curPlayer->me->body, curPlayer->jump);
	}
}
