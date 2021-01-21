typedef struct Player {
	Actor *me;
	Action *jump;
	Action *move;
	int speed;
} Player;

Player *makePlayer();
void deletePlayer(Player *);
void keyPressPlayer(Player *, char);
void keyReleasePlayer(Player *, char);
