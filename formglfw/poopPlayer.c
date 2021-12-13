#include "poopPlayer.h"

PoopGuy *myPooper;
Player *myPlayer;

void makePoopPlayer(Player *p, PoopGuy *pg) {
	myPooper = pg;
	myPlayer = p;
	//key mouse ocntrols
	if (p->num == 0) {
		addControl(p, "K0W", up);
		addControl(p, "K0A", left);
		addControl(p, "K0S", down);
		addControl(p, "K0D", right);
		addControl(p, "M01", toggleEat);
		addControl(p, "M00", poop);
		addControl(p, "K0 ", jumpStart);
	} else {
		addControl(p, "K0I", up);
		addControl(p, "K0J", left);
		addControl(p, "K0K", down);
		addControl(p, "K0L", right);
		addControl(p, "M01", toggleEat);
		addControl(p, "M00", poop);
		addControl(p, "K0 ", jumpStart);
	}

	/*
	//gamepad controls
	addControl(p, "A00", xmInp);
	addControl(p, "A01", ymInp);
	addControl(p, "A05", poopInp);
	addControl(p, "A04", eatInp);
	addControl(p, "J00", jumpInp);
	*/
}
