int terminalVelocity = 9;
Action *makeGravity() {
	moveVar *mv = makeMoveVar(); //uses its own moveVar, to avoid freeing a pointer that has already been freed
	Action *a = makeAction(&gravity, mv);
	a->active = 1;
	return a;
}

void gravity(Form *f, Action *a) {
	moveVar *mv = (moveVar*)(a->vars);
	if (checkCol(f->pos[0], f->pos[1] - 1) == 0) {
		if (mv->force[1] < terminalVelocity * mv->mass) {
			addForce(mv, 0, -1, 0, 1);
		}
	} else {
		setForce(mv, -1, 0);
	}
	move(f, a);
}
