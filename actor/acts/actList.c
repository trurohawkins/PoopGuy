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
	return mv;
}


void move(Form *f, Action *a) {
	moveVar *mv = (moveVar *)(a->vars);
	if (!(mv->force[0] == 0 && mv->force[1] == 0)) {
		//printf("moving %i, %i\n", mv->force[0], mv->force[1]);
	}
	if (mv->force[0] != 0) {
		int speed = (mv->forceCounter[0] + mv->force[0]) / mv->mass;
		mv->forceCounter[0] = (int)(mv->forceCounter[0] + mv->force[0]) % mv->mass;
		//mv->force[0] = 0;
		for (int i = 0; i < speed; i++) {
			int p = f->pos[0] + mv->dir[0];
			if (checkCol(p, f->pos[1]) == 0) {
				removeForm(f->pos[0], f->pos[1]);
				placeForm(p, f->pos[1], f);
			}
		}
	//	mv->dir[0] = 0;
	}
	if (mv->force[1] != 0) {
		int speed = (mv->forceCounter[1] + mv->force[1]) / mv->mass;
		mv->forceCounter[1] = (int)(mv->forceCounter[1] + mv->force[1]) % mv->mass;
	//	mv->force[1] = 0;
		for (int i = 0; i < speed; i++) {
			float p = f->pos[1] + mv->dir[1];
			if (checkCol(f->pos[0], p) == 0) {
				removeForm(f->pos[0], f->pos[1]);
				placeForm(f->pos[0], p, f);
			}
		}
	//	mv->dir[1] = 0;
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

void addForce(void *m, int x, int y, int powX, int powY) {
	moveVar *mv = (moveVar*)m;
	if (x != 0 && powX != 0) {
		if((mv->dir[0] <= 0 && x < 0) || (mv->dir[0] >= 0 && x > 0)) {
			mv->force[0] += powX;
		} else {
			mv->force[0] -= powX;
		}
		/*
		if (mv->dir[0] == 0) {
			mv->dir[0] = x;
		} else {
			mv->dir[0] = (mv->dir[0] + x) / 2;
		}
		*/
		if (mv->dir[0] != x) {
			mv->dir[0] += x;
		}
	}
	if (y != 0 && powY != 0) {
		if((mv->dir[1] <= 0 && y < 0) || (mv->dir[1] >= 0 && y > 0)) {
			mv->force[1] += powY;
		} else {
			mv->force[1] -= powY;
		}
		if (mv->dir[1] != y) {
			mv->dir[1] += y;
		}
		printf("%i\n", mv->force[1]);
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

Form *checkCol(int x, int y) {
	if (x >= 0 && y >= 0 && x < theWorld->x && y < theWorld->y) {
		return theWorld->map[x][y];
	} else {
		if (inert == 0) {
			makeInert();
		}	
		return inert;
	}
}
#include "gravity.c"
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

