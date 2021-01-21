Action *makeStomach() {
	eatPooVar *ep= (eatPooVar*)calloc(1, sizeof(eatPooVar));
	ep->stomach = makeList();
	Action *stom = makeAction(&stomachStuff, ep);
	stom->active = 1;
	return stom;
}

void stomachStuff(Form *f, Action *a) {
	eatPooVar *ep = (eatPooVar*)(a->vars);
	int **d = getDirs();
	Form *food = removeForm(f->pos[0] + d[ep->dir][0], f->pos[1] + d[ep->dir][1]);//checkCol(f->pos[0] + 1, f->pos[1]);

	if (food != NULL && food->pos[0] > -1) {
		addToStack(food, a);
	}
}

void addToStack(Form *f, Action *a) {
	eatPooVar *ep = (eatPooVar*)(a->vars);
	linkedList *cur = ep->stomach;
	while (cur->data != NULL) {
		formStack *fs = (formStack*)(cur->data);
		if (compareForms(f, fs->type) == 1) { //we have a match
			fs->count++;
			printf("adding to stack, now:%i\n", fs->count);
			f = 0;
			break;
		}
		if (cur->next == 0) {
			cur->next = makeList();
		}
		cur = cur->next;
	}
	if (f != 0) {
		printf("new stack\n");
		formStack *fs  = (formStack*)calloc(1, sizeof(formStack));
		fs->type = f;
		fs->count = 1;
		cur->data = fs;
	}

}


