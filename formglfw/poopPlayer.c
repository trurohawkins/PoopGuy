#include "poopPlayer.h"


PoopGuy *makePoopPlayer(int xp, int yp, int pNum, GLuint tc, GLuint ts) {
		PoopGuy *pooper = makePoopGuy(3, 3);
		placeForm(xp, yp, pooper->me->body);
		checkSide(pooper->me->body, 1, 0, true);
		addActor(pooper->me);

		Anim *poo = makeAnim("resources/poopGuySpriteSheet.png", 4, 6, tc, ts);
		setScale(poo, 4, 4);
		for (int i = 1; i < 4; i++) {
			addSprite(poo, i, 6);
		}
		GLuint spriteVao = makeSpriteVao(1, 1);
		animAddVao(poo, spriteVao);//makeSpriteVao(1, 1));
		setAnim(pooper->me->body, poo);

		Player *p = makePlayer(pooper, pNum, deletePoopGuy);
	
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
		addControl(p, "K0O", toggleEat);
		addControl(p, "K0U", poop);
		addControl(p, "K0M", jumpStart);
	}

	/*
	//gamepad controls
	addControl(p, "A00", xmInp);
	addControl(p, "A01", ymInp);
	addControl(p, "A05", poopInp);
	addControl(p, "A04", eatInp);
	addControl(p, "J00", jumpInp);
	*/
	return pooper;
}
