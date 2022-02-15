#include "../actor/PoopGuy.h"

PoopGuy *makePoopPlayer (int xp, int yp, int pNum);
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

