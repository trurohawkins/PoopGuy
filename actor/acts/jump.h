typedef struct jumpVar {
	moveVar *move;
	Action *grav;
	int curJP;
	int jpGoal;
	int maxJP;
	int jumpPow;
} jumpVar;

Action *makeJump(moveVar *mv, Action *n_grav);
void jump(Form *f, Action* a);
