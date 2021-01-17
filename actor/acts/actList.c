void move(Form *f, Action *a) {
	moveVar *mv = (moveVar *)(a->vars);
	if (mv->speedCounter == mv->speed) {
		int mx = f->pos[0] + dirs[mv->dir][0];
		int my = f->pos[1] + dirs[mv->dir][1];
		if (checkCol(mx, my) == 0) {
			removeForm(f->pos[0], f->pos[1]);
			placeForm(mx, my, f);
		}
		mv->speedCounter = 0;
	} else {
		mv->speedCounter++;
	}
}

void setMoveSpeed(void *m, int n_speed) {
	moveVar *mv = (moveVar*)m;
	mv->speed = n_speed;
}

void setMoveDir(void *m, int n_dir) {
	moveVar *mv = (moveVar*)m;
	mv->dir = n_dir;
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
