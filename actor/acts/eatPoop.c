Action *makeStomach() {
	eatPooVar *ep= (eatPooVar*)calloc(1, sizeof(eatPooVar));
	ep->stomach = makeList();
	ep->pooping = 0;
	Action *stom = makeAction(&stomachStuff, ep);
	stom->active = 1;
	return stom;
}

void stomachStuff(Form *f, Action *a) {
	eatPooVar *ep = (eatPooVar*)(a->vars);
	int **d = getDirs();
	Form *food = removeForm(f->pos[0] + d[ep->dir][0], f->pos[1] + d[ep->dir][1]);//checkCol(f->pos[0] + 1, f->pos[1]);

	if (food != NULL) {
		addToStack(food, a);
	} 
	if (ep->pooping != 0) {
		Form *poo = removeFromStack(a);
		if (poo != 0) {

			int buttDir = (ep->dir + 2) % 4;
			int pooX = f->pos[0] + d[buttDir][0]; 
			int pooY = f->pos[1] + d[buttDir][1]; 
			if (checkCol(pooX, pooY) != NULL) {
				int mx = f->pos[0] + d[ep->dir][0];
				int my = f->pos[1] + d[ep->dir][1];
				if (checkCol(mx, my) == 0) {
					removeForm(f->pos[0], f->pos[1]);
					placeForm(mx, my, f);
					pooX = f->pos[0] + d[buttDir][0]; 
					pooY = f->pos[1] + d[buttDir][1]; 
				}
			}
			placeForm(pooX, pooY, poo);
		}
		ep->pooping = 0;
	}
}

void addToStack(Form *f, Action *a) {
	eatPooVar *ep = (eatPooVar*)(a->vars);
	linkedList *cur = ep->stomach;
	while (cur->data != NULL) {
		formStack *fs = (formStack*)(cur->data);
		if (compareForms(f, fs->type) == 1) { //we have a match
			fs->count++;
			f = 0;
			break;
		}
		if (cur->next == 0) {
			cur->next = makeList();
		}
		cur = cur->next;
	}
	if (f != 0) {
		formStack *fs  = (formStack*)calloc(1, sizeof(formStack));
		fs->type = f;
		fs->count = 1;
		cur->data = fs;
	}
}

Form *removeFromStack(Action *a) {
	eatPooVar *ep = (eatPooVar*)(a->vars);
	Form *poop = 0;
	if (ep->stomach != 0 && ep->stomach->data != 0) {
		formStack *fs = (formStack*)(ep->stomach->data);
		fs->count--;
		poop = fs->type;
		if (fs->count == 0) {
			linkedList *oh = ep->stomach;
			ep->stomach = ep->stomach->next;
			free(oh);
			free(fs);
			if (ep->stomach == 0) {
				ep->stomach = makeList();
			}
		}
	}
	return poop;
}
