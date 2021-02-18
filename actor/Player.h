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

Player *makePlayer();
void deletePlayer(Player *);
void keyPressPlayer(Player *, char);
void keyReleasePlayer(Player *, char);