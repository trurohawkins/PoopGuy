typedef struct moveVar {
	int speedCounter;
	int speed;
	int dir[2];
	int force[2];
	int mass;
	int forceCounter[2];
} moveVar;

Action *makeMove();
moveVar *makeMoveVar();
void move(Form *f, Action *a);
void setMoveSpeed(void *m, int n_speed);
void setMoveDirX(void *m, int n_dir);
void setMoveDirY(void *m, int n_dir);
void setMoveMass(void *m, int n_mass);
void addForce(void *m, int powX, int powY);
Form *checkCol(int x, int y);
#include "gravity.h"
#include "jump.h"
#include "eatPoop.h"
