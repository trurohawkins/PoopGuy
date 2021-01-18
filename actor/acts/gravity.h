typedef struct gravVar {
	moveVar *move;
} gravVar;

Action *makeGravity();
void gravity(Form *f, Action *a);
