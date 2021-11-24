#include "PoopGuy.h"

PoopGuy *makePoopGuy (int sx, int sy) {
	PoopGuy *pooper = (PoopGuy *)calloc(1, sizeof(PoopGuy));
	pooper->speed = 10;
	pooper->maxForce = 10;
	pooper->me = makeActor(makeForm(0.2, 1, 0.2, sx, sy));
	pooper->me->body->id = 69;
	pooper->move = makeMove();
	Action *grav = makeGravity(pooper->move->vars);
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
	//pg = pooper;
	return pooper;
}
/*
PoopGuy *getPoopGuy() {
	return pg;
}
*/

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

void up(PoopGuy *pg, float val) {
	if (val > 0) {
		eatPooVar *ep = (eatPooVar*)(pg->eatPoop->vars);
		changeDir(ep, pg->me->body,0);
	}
}

void left(PoopGuy *pg, float val) {
	controlVar *cv = (controlVar*)pg->control->vars;
	eatPooVar *ep = (eatPooVar*)(pg->eatPoop->vars);
	if (val > 0) {
		changeDir(ep, pg->me->body, 1);
		cv->moveLeft = 1;
	} else {
		cv->moveLeft = 0;
	}
}

void right(PoopGuy *pg, float val) {
	controlVar *cv = (controlVar*)pg->control->vars;
	eatPooVar *ep = (eatPooVar*)(pg->eatPoop->vars);
	if (val > 0) {	
		changeDir(ep, pg->me->body, 3);
		cv->moveRight = 1;
	} else {
		cv->moveRight = 0;
	}
}
void down(PoopGuy *pg, float val) {
	if (val > 0) {
		eatPooVar *ep = (eatPooVar*)(pg->eatPoop->vars);
		changeDir(ep, pg->me->body,2);
	}
}

void xMove(PoopGuy *pg, float val) {
	if (val > 0) {
		right(pg, 1);
	}  else if (val < 0) {
		left(pg, 1);
	} else {
		right(pg, 0);
		left(pg, 0);
	}
}
void yMove(PoopGuy *pg, float val) {
	if (val > 0) {
		up(pg, 1);
	}  else if (val < 0) {
		down(pg, 1);
	} else {
		up(pg, 0);
		down(pg, 0);
	}
}

void poop(PoopGuy *pg, float val) {
	eatPooVar *ep = (eatPooVar*)(pg->eatPoop->vars);
	if (val > 0) {
		ep->pooping = 1;
	} else {
		ep->pooping = 0;
	}
}

void toggleEat(PoopGuy *pg, float val) {
	if (val > 0) {//only if when pressed not released
		eatPooVar *ep = (eatPooVar*)(pg->eatPoop->vars);
		ep->eating = (ep->eating+1)%2;
	}
}

void jumpStart(PoopGuy *pg, float val) {
	if (val > 0) {
		startJump(pg->me->body, pg->jump);
	}
}
