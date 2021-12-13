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

void up(void *pg, float val);
void left(void *pg, float val);
void down(void *pg, float val);
void right(void *pg, float val);
void xMove(void *pg, float val);
void yMove(void *pg, float val);
void poop(void *pg, float val);
void toggleEat(void *pg, float val);
void jumpStart(void *pg, float val);

void setAnimSprite(PoopGuy *pg);
#endif
