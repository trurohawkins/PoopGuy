typedef struct moveVar {
	int speedCounter;
	int speed;
	int dir;
} moveVar;

void move(Form *f, Action *a);
void setMoveSpeed(void *m, int n_speed);
void setMoveDir(void *m, int n_dir);
Form *checkCol(int x, int y);
