int terminalVelocity = -9;
Action *makeGravity(moveVar *mv) {
	gravVar *gv = (gravVar*)calloc(1, sizeof(gravVar));
	gv->move = mv;
	//moveVar *mv = makeMoveVar(); //uses its own moveVar, to avoid freeing a pointer that has already been freed
	Action *a = makeAction(&gravity, gv);
	a->active = 1;
	return a;
}

void gravity(Form *f, Action *a) {
	gravVar *gv = (gravVar*)a->vars;
	moveVar *mv = gv->move;
	if (checkCol(f->pos[0], f->pos[1] - 1) == 0) {
		if (mv->force[1] > terminalVelocity * mv->mass) {
			addForce(mv, 0, -1);
			//printf("grav: %i\n", mv->force[1]);
		}
	} else {
		setForce(mv, -1, 0);
	}
	move(f, a);
}
