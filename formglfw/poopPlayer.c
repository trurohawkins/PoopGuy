#include "poopPlayer.h"

PoopGuy *myPooper;
Player *myPlayer;

void makePoopPlayer(Player *p, PoopGuy *pg) {
	myPooper = pg;
	myPlayer = p;
	//key mouse ocntrols
	addControl(p, "K0W", upInp);
	addControl(p, "K0A", leftInp);
	addControl(p, "K0S", downInp);
	addControl(p, "K0D", rightInp);
	addControl(p, "M01", eatInp);
	addControl(p, "M00", poopInp);
	addControl(p, "K0 ", jumpInp);
	//gamepad controls
	addControl(p, "A00", xmInp);
	addControl(p, "A01", ymInp);
	addControl(p, "A05", poopInp);
	addControl(p, "A04", eatInp);
	addControl(p, "J00", jumpInp);
}

void upInp(float val) {
	Anim *a = myPlayer->sprite;
	up(myPooper, val);
	setFlipX(a, 1);
	setRoto(a, 0);
	setSprite(a);
}
void leftInp(float val) {
	Anim *a = myPlayer->sprite;
	setFlipX(a, -1);
	setRoto(a, 1);
	left(myPooper, val);
	setSprite(a);
}
void downInp(float val) {
	Anim *a = myPlayer->sprite;
	setRoto(a, 2);
	setFlipX(a, 1);
	down(myPooper, val);
	setSprite(a);
}
void rightInp(float val) {
	Anim *a = myPlayer->sprite;
	setRoto(a, 3);
	setFlipX(a, 1);
	right(myPooper, val);
	setSprite(a);
}

void xmInp(float val) {
	Anim *a = myPlayer->sprite;
	xMove(myPooper, val);
	if (val > 0) {
		setRoto(a, 3);
		setFlipX(a, 1);
	} else if (val < 0) {
		setRoto(a, 1);
		setFlipX(a, -1);
	}
	setSprite(a);
}
void ymInp(float val) {
	Anim *a = myPlayer->sprite;
	yMove(myPooper, val);
	if (val > 0) {
		setRoto(a, 0);
		setFlipX(a, 1);
	} else if (val < 0) {
		setRoto(a, 2);
		setFlipX(a, 1);
	}
	setSprite(a);
}
void poopInp(float val) {
	poop(myPooper, val);
}
void eatInp(float val) {
	Anim *a = myPlayer->sprite;
	toggleEat(myPooper, val);
	setSprite(a);
}
void jumpInp(float val) {
	jumpStart(myPooper, val);
}

void setSprite(Anim *a) {
	eatPooVar *ep = (eatPooVar*)(myPooper->eatPoop->vars);
	controlVar *cv = (controlVar*)(myPooper->control->vars);
	bool walking = cv->moveLeft > 0 || cv->moveRight > 0;
	if (walking) {
		if (ep->eating) {
			changeSprite(a, 3);
		} else {
			changeSprite(a, 2);	
		}
	} else {
		if (ep->eating) {
			changeSprite(a, 1);
		} else {
			changeSprite(a, 0);	
		}
	}
}

void walkSprite(Anim *a, bool walking) {
	eatPooVar *ep = (eatPooVar*)(myPooper->eatPoop->vars);
	if (walking) {
		if (ep->eating == false) {
			changeSprite(a, 2);
		} else {
			changeSprite(a, 3);
		}
	} else {
		if (ep->eating == false) {
			changeSprite(a, 0);
		} else {
			changeSprite(a, 1);
		}
	}
}
