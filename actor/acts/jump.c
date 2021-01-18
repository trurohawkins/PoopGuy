Action *makeJump(moveVar *mv, Action *n_grav) {
	jumpVar *jv = (jumpVar*)calloc(1, sizeof(jumpVar));
	jv->move = mv;
	jv->grav = n_grav;
	jv->maxJP = 10;
	jv->jumpPow = 2;
	Action *a = makeAction(&jump, jv);
	a->active = 0;
	return a;
}

void startJump(Action *a) {
	if (a->active == 0) {
		jumpVar *jv = (jumpVar*)a->vars;
		jv->jpGoal = jv->maxJP;
		jv->curJP = 0;
		setForce(jv->move, -1, 0);
		jv->grav->active = 0;
		a->active = 1;
	}
}

void jump(Form *f, Action *a) {
	jumpVar *jv = (jumpVar*)a->vars;
	int dir = 0;
	if(jv->curJP != jv->jpGoal) {
		dir = sign(jv->jpGoal - jv->curJP);
		jv->curJP += dir;
	} else if (jv->jpGoal > 0){
		jv->jpGoal = 0;
	} else {
		a->active = 0;
		jv->grav->active = 1;
	//	printf("jump done %i\n", jv->move->force[1]);	
	}
	if (a->active != 0) {
	//	printf("jumping in %i, at%i\n", dir, jv->move->force[1]);	
		addForce(jv->move, 0, dir * jv->jumpPow);
	}
}
