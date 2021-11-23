#ifndef POOPGUY
#define POOPGUY

typedef struct PoopGuy {
	Actor *me;
	Action *jump;
	Action *move;
	Action *eatPoop;
	Action *control;
	int speed;
	int maxForce;
	char lastInp;

} PoopGuy;


PoopGuy *makePoopGuy(int sx, int sy);
PoopGuy *getPoopGuy();
void deletePoopGuy(PoopGuy *);
void keyPressPoopGuy(PoopGuy *, char);
void keyReleasePoopGuy(PoopGuy *, char);

void up(float val);
void left(float val);
void down(float val);
void right(float val);
void xMove(float val);
void yMove(float val);
void poop(float val);
void toggleEat(float val);
void jumpInp(float val);
#endif
