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

void up(PoopGuy *pg, float val);
void left(PoopGuy *pg, float val);
void down(PoopGuy *pg, float val);
void right(PoopGuy *pg, float val);
void xMove(PoopGuy *pg, float val);
void yMove(PoopGuy *pg, float val);
void poop(PoopGuy *pg, float val);
void toggleEat(PoopGuy *pg, float val);
void jumpStart(PoopGuy *pg, float val);
#endif
