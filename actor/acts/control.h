typedef struct controlVar {
	int moveLeft;
	int moveRight;
	int mrCount;
	int mlCount;
	PoopGuy *pooper;
} controlVar;

Action *makeControl();
void setPoopGuy(void *c, PoopGuy *n_pooper);
void control(Form *f, Action *a);
