#include "PoopGuy.h"
PoopGuy *curPoopGuy;

PoopGuy *makePoopGuy (int sx, int sy) {
	PoopGuy *pooper = (PoopGuy *)calloc(1, sizeof(PoopGuy));
	pooper->speed = 10;
	pooper->maxForce = 10;
	pooper->me = makeActor(makeForm(0.2, 1, 0.2, sx, sy));
	pooper->me->body->id = 69;
	pooper->move = makeMove();
	Action *grav = makeGravity(pooper->move->vars);
	setFriction(grav, 10);
	pooper->jump = makeJump(pooper->move->vars, grav);
	pooper->eatPoop = makeStomach(pooper->me->body, sx, sy);
	pooper->control = makeControl();
	setPoopGuy(pooper->control->vars, pooper);
	addAction(pooper->me, pooper->move);
	addAction(pooper->me, grav);
	addAction(pooper->me, pooper->jump);
	addAction(pooper->me, pooper->eatPoop);
	addAction(pooper->me, pooper->control);
	//changeDir(pooper->eatPoop pooper->me->body, 3);
	//cv->moveRight = 1;
	curPoopGuy = pooper;
	return pooper;
}

PoopGuy *getPoopGuy() {
	return curPoopGuy;
}

void deletePoopGuy(PoopGuy *pooper) {
	eatPooVar *ep = (eatPooVar*)(pooper->eatPoop->vars);
	freeList(&(ep->stomach));
	free(pooper);
}

void keyPressPoopGuy(PoopGuy *pooper, char input) {
	eatPooVar *ep = (eatPooVar*)(pooper->eatPoop->vars);
	moveVar *mv = (moveVar*)pooper->move->vars;
	//printf("%c\n", input);
	controlVar *cv = (controlVar*)pooper->control->vars;
	switch (input) {
		case 65: //a
			changeDir(ep, pooper->me->body, 1);
			cv->moveLeft = 1;
			break;
		case 68: //d
			changeDir(ep, pooper->me->body, 3);
			cv->moveRight = 1;
			break;
		case 69:
			ep->eating = (ep->eating+1)%2;
			break;
		case 87://w
			changeDir(ep, pooper->me->body,0);
			break;
		case 83://s
			changeDir(ep, pooper->me->body,2);
			break;
		case 80:
			ep->pooping = 1;
			break;
		case 32:
			startJump(pooper->me->body, pooper->jump);
			break;
	}
	if (input == 97 || input == 100) {
		pooper->lastInp = input;
	}
}

void keyReleasePoopGuy(PoopGuy *pooper, char input) {
	eatPooVar *ep = (eatPooVar*)(pooper->eatPoop->vars);
	controlVar *cv = (controlVar*)pooper->control->vars;
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
		eatPooVar *ep = (eatPooVar*)(curPoopGuy->eatPoop->vars);
		changeDir(ep, curPoopGuy->me->body,0);
	}
}

void left(float val) {
	controlVar *cv = (controlVar*)curPoopGuy->control->vars;
	eatPooVar *ep = (eatPooVar*)(curPoopGuy->eatPoop->vars);
	if (val > 0) {
		changeDir(ep, curPoopGuy->me->body, 1);
		cv->moveLeft = 1;
	} else {
		cv->moveLeft = 0;
	}
}

void right(float val) {
	controlVar *cv = (controlVar*)curPoopGuy->control->vars;
	eatPooVar *ep = (eatPooVar*)(curPoopGuy->eatPoop->vars);
	if (val > 0) {	
		changeDir(ep, curPoopGuy->me->body, 3);
		cv->moveRight = 1;
	} else {
		cv->moveRight = 0;
	}
}
void down(float val) {
	if (val > 0) {
		eatPooVar *ep = (eatPooVar*)(curPoopGuy->eatPoop->vars);
		changeDir(ep, curPoopGuy->me->body,2);
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
	eatPooVar *ep = (eatPooVar*)(curPoopGuy->eatPoop->vars);
	if (val > 0) {
		ep->pooping = 1;
	} else {
		ep->pooping = 0;
	}
}

void toggleEat(float val) {
	if (val > 0) {//only if when pressed not released
		eatPooVar *ep = (eatPooVar*)(curPoopGuy->eatPoop->vars);
		ep->eating = (ep->eating+1)%2;
	}
}

void jumpInp(float val) {
	if (val > 0) {
		startJump(curPoopGuy->me->body, curPoopGuy->jump);
	}
}
