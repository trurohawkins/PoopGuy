#include "poopPlayer.h"


PoopGuy *makePoopPlayer(int xp, int yp, int pNum, GLuint tc, GLuint ts) {
	PoopGuy *pooper = makePoopGuy(3, 3);
	placeForm(xp, yp, pooper->me->body);
	checkSide(pooper->me->body, 1, 0, true);
	addActor(pooper->me);
	char *baseFile = "resources/poopGuySpriteSheet.png"; 
	int numColors = 7;
	bool generated = false;
	char **sprites = (char**)calloc(sizeof(char*), numColors);
	int sLen = strlen(baseFile);
	if (numColors > 1) {
		generated = true;
		for (int i = 0; i < numColors; i++) {
			sprites[i] = (char*)calloc(sizeof(char), sLen + 2);
			sprites[i][sLen-4] = (unsigned char)i + 48;
			strncpy(sprites[i], baseFile, sLen - 4);
			strcat(sprites[i], ".png");
		}
	} else {
		*sprites = (char*)calloc(sizeof(char), sLen + 1);
		strcpy(*sprites, baseFile); 
	}
	Anim *poo = makeAnim(sprites, numColors, generated, 4, 6, tc, ts);
	for (int i = 0; i < numColors; i++) {
		free(sprites[i]);
	}
	free(sprites);
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
		if (numColors != 1) {
			float poopguyPalette0[21] = {0.023529, 0.188235, 0.027451, 0.090196, 0.737255, 0.109804, 0.098039, 0.811765, 0.121569, 0.109804, 0.862745, 0.133333, 1.000000, 1.000000, 1.000000, 0.098039, 0.772549, 0.117647, 0.105882, 0.831373, 0.129412};
			loadPalette(poo, poopguyPalette0);
		}
		addControl(p, "K0W", up);
		addControl(p, "K0A", left);
		addControl(p, "K0S", down);
		addControl(p, "K0D", right);
		addControl(p, "M01", toggleEat);
		addControl(p, "M00", poop);
		addControl(p, "K0 ", jumpStart);
	} else {
		if (numColors != 1) {
			float palette[21] = {0.0,0.0,0.0,  0.4,0,0.2,  0.3,0,0.1, 0.8,0,0.2,  1,1,1,  0.9,0.1,0.2, 0.50,0,0};
			loadPalette(poo, palette);
		}
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
