#ifndef PLAYER
#define PLAYER

typedef struct Player {
	Actor *me;
	Action *jump;
	Action *move;
	Action *eatPoop;
	Action *control;
	int speed;
	int maxForce;
	char lastInp;

} Player;


Player *makePlayer(int sx, int sy);
Player *getPlayer();
void deletePlayer(Player *);
void keyPressPlayer(Player *, char);
void keyReleasePlayer(Player *, char);

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
