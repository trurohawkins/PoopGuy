Action *makeMove() {
	moveVar *mv = makeMoveVar();
	Action *a = makeAction(&move, mv);
	a->active = 1;
	return a;
}

moveVar *makeMoveVar() {
	moveVar *mv = (moveVar*)calloc(1, sizeof(moveVar));
	mv->mass = 10;
	//mv-> forceCounter[2] = {0,0};
//	mv->force[2] = {0, 0};
	mv->forceCounter[0] = 0;
	mv->forceCounter[1] = 0;
	mv->force[0] = 0;
	mv->force[1] = 0;
	mv->dir[0] = 0;
	mv->dir[1] = 0;
	mv->decel[0] = 0;
	mv->decel[1] = 0;
	mv->decelCounter[0] = 0;
	mv->decelCounter[1] = 0;
	mv->decelSpeed[0] = 10;
	mv->decelSpeed[1] = 0;
	return mv;
}


void move(Form *f, Action *a) {
	moveVar *mv = (moveVar *)(a->vars);
	if (!(mv->force[0] == 0 && mv->force[1] == 0)) {
		//printf("moving %i, %i\n", mv->force[0], mv->force[1]);
	}
	if (mv->force[0] != 0) {
		int speed = (mv->forceCounter[0] + abs(mv->force[0])) / mv->mass;
		mv->forceCounter[0] = (int)(mv->forceCounter[0] + abs(mv->force[0])) % mv->mass;
		//printf("moving: speed: %i\n", speed);
		for (int i = 0; i < speed; i++) {
			int p = f->pos[0] + sign(mv->force[0]);
			if (checkSide(f, sign(mv->force[0]), 0, true) == 0) {
				removeForm(f);
				placeForm(p, f->pos[1], f);
			}
		}
	}
	if (mv->force[1] != 0) {
		int speed = (mv->forceCounter[1] + abs(mv->force[1])) / mv->mass;
		mv->forceCounter[1] = (int)(mv->forceCounter[1] + abs(mv->force[1])) % mv->mass;
		for (int i = 0; i < speed; i++) {
			int p = f->pos[1] + sign(mv->force[1]);//mv->dir[1];
			if (checkSide(f, 0, sign(mv->force[1]), true) == 0) {
				//printf("moving form Y val from %f to %i\n", f->pos[1], p);
				removeForm(f);
				placeForm(f->pos[0], p, f);
			}
		}
	}
	decelerate(mv);
}

void decelerate(moveVar *mv) {
	for (int i = 0; i < 2; i++) {
		if (mv->force[i] != 0) {
			if (mv->decelCounter[i] >= mv->decel[i]) {
				if (mv->force[i] > 0) {
					if (mv->force[i] - mv->decelSpeed[i] > 0) {
						mv->force[i] -= mv->decelSpeed[i];
					} else {
						mv->force[i] = 0;
					}
				} else if (mv->force[i] < 0) {
					if (mv->force[i] + mv->decelSpeed[i] < 0) {
						mv->force[i] += mv->decelSpeed[i];
		 			} else {
						mv->force[i] = 0;
					}
				}
				mv->decelCounter[i] = 0;
			} else {
				mv->decelCounter[i]++;
			}
		}
	}
}

Form *checkCol(int x, int y) {
	if (x >= 0 && y >= 0 && x < theWorld->x && y < theWorld->y) {
		return checkForm(x,y);//SolidForm(theWorld->map[x][y]);
	} else {
		if (inert == 0) {
			makeInert();
		}	
		return inert;
	}
}

void addForce(void *m, int powX, int powY) {
	moveVar *mv = (moveVar*)m;
	if (powX != 0) {
		mv->force[0] += powX;
		//printf("adding force = %i\n", mv->force[0]);
	}
	if (powY != 0) {
		mv->force[1] += powY;
	}

}


void setForce(void *m, int x, int y) {
	moveVar *mv = (moveVar*)m;
	if (x >= 0) {
		mv->force[0] = x;
	}
	if (y >= 0) {
		mv->force[1] = y;
	}
}


void setMoveSpeed(void *m, int n_speed) {
	moveVar *mv = (moveVar*)m;
	mv->speed = n_speed;
}

void setMoveDirX(void *m, int n_dir) {
	moveVar *mv = (moveVar*)m;
	mv->dir[0] = n_dir;
}

void setMoveDirY(void *m, int n_dir) {
	moveVar *mv = (moveVar*)m;
	mv->dir[1] = n_dir;
}

void setMoveMass(void *m, int n_mass) {
	moveVar *mv = (moveVar*)m;
	mv->mass = n_mass;
}

void setDecel(void *m, int xory, int d_interval, int d_speed) {
	moveVar *mv = (moveVar*)m;
	if (xory != 0 && xory != 1) {
		for (int i = 0; i < 2; i++) {
			mv->decel[i] = d_interval;
			mv->decelSpeed[i] = d_speed;
		}
	} else {
		mv->decel[xory] = d_interval;
		mv->decel[xory] = d_speed;
	}
}

#include "gravity.c"
#include "jump.c"
#include "eatPoop.c"
/* old move
	if (mv->speedCounter == mv->speed) {
		int mx = f->pos[0] + mv->dir[0];
		int my = f->pos[1] + mv->dir[1];
		if (checkCol(mx, my) == 0) {
			removeForm(f->pos[0], f->pos[1]);
			placeForm(mx, my, f);
		}
		mv->speedCounter = 0;
	} else {
		mv->speedCounter++;
	}
*/

