typedef struct controlVar {
	int moveLeft;
	int moveRight;
	int mrCount;
	int mlCount;
	Player *player;
} controlVar;

Action *makeControl();
void setPlayer(void *c, Player *n_player);
void control(Form *f, Action *a);
