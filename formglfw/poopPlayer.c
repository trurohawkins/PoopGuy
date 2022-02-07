#include "poopPlayer.h"


PoopGuy *makePoopPlayer(int xp, int yp, int pNum, GLuint tc, GLuint ts) {
	PoopGuy *pooper = makePoopGuy(3, 3);
	placeForm(xp, yp, pooper->me->body);
	checkSide(pooper->me->body, 1, 0, true);
	addActor(pooper->me);

	Anim *poo = makeAnim("resources/poopGuySpriteSheet.png", 4, 6, tc, ts);
	//Anim *poo = makeAnim("resources/Heart2.png", 1, 1, tc, ts);
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
	float palette[21] = {0.0,0.0,0.0,  0.4,0,0.2,  0.3,0,0.1, 0.8,0,0.2,  1,1,1,  0.9,0.1,0.2, 0.50,0,0};
		loadPalette(poo, palette);
		addControl(p, "K0I", up);
		addControl(p, "K0J", left);
		addControl(p, "K0K", down);
		addControl(p, "K0L", right);
		addControl(p, "K0O", toggleEat);
		addControl(p, "K0U", poop);
		addControl(p, "K0M", jumpStart);
	}
	makeJoyButtControl(p, ';', up);
	makeJoyButtControl(p, '>', left);
	makeJoyButtControl(p, '=', down);
	makeJoyButtControl(p, '<', right);
	makeJoyButtControl(p, '0', jumpStart);
	makeJoyAxeControl(p, '5', poop);
	makeJoyAxeControl(p, '2', toggleEat);
	makeJoyAxeControl(p, '3', poop);
	makeJoyAxeControl(p, '4', toggleEat);
	makeJoyAxeControl(p, '0', xMove);
	makeJoyAxeControl(p, '1', yMove);
	return pooper;
}
