Action *makeStomach(Form *f, float bite) {
	eatPooVar *ep= (eatPooVar*)calloc(1, sizeof(eatPooVar));
	ep->stomach = makeList();
	ep->pooping = 0;
	ep->eating = 0;
	ep->bite[0] = 1;//smaller length for rect bite
	ep->bite[1] =	bite;
	changeDir(ep, f, 3);
	Action *stom = makeAction(&stomachStuff, ep);
	stom->active = 1;
	return stom;
}

void changeDir(eatPooVar *ep, Form* f, int dir) {
	ep->dir = dir;
	if (dir%2 == 0) {//assuming 4 directions
		ep->xBite = ep->bite[1] - f->pMod[0];
		ep->yBite = ep->bite[0];
	} else {
		ep->xBite = ep->bite[0];
		ep->yBite = ep->bite[1] - f->pMod[1];
	}
}

void stomachStuff(Form *f, Action *a) {
	eatPooVar *ep = (eatPooVar*)(a->vars);
	int **d = getDirs();
	if (ep->eating != 0) {
		Form *food = NULL;
		int mpx = f->pos[0] + (f->pMod[0] * d[ep->dir][0]);
		int mpy = f->pos[1] - (1-f->pMod[0]);
		int xd = d[ep->dir][0];
		int yd = 1;	
		if (ep->dir % 2 == 0) {
			yd = d[ep->dir][1];
			xd = 1;
			mpy = f->pos[1] + (f->pMod[1] * d[ep->dir][1]);
			mpx = f->pos[0] - (1-f->pMod[1]);
		} 
		int xc = mpx + (((f->size[0]/2)+1) * xd);
		int yc = mpy + (((f->size[1]/2)+1) * yd);
		for (int x = 0; x < ep->xBite; x++) {
			for (int y = 0; y < ep->yBite; y++) {
				Form *tmp = takeForm(xc - x, yc - y);
				if (tmp != NULL && food == NULL) {
					addToStack(tmp, a);
					//food = tmp;
				}
			}
		}
		if (food != NULL) {
			addToStack(food, a);
		} 
	}
	if (ep->pooping != 0) {
		Form *poo = removeFromStack(a);
		if (poo != NULL) {
			int buttDir = (ep->dir + 2) % 4;
			bool poopGood = true;
			if (checkSide(f, d[buttDir][0], d[buttDir][1], false) != NULL) {
				if (checkSide(f, d[ep->dir][0], d[ep->dir][1], true) == NULL) {
					removeForm(f);
					placeForm(f->pos[0] + d[ep->dir][0], f->pos[1] + d[ep->dir][1], f);
				} else {
					Form *block =checkSide(f, d[ep->dir][0], d[ep->dir][1], false);
					poopGood = false;
				}
			}
			if (poopGood) {
				addToStack(poo, a);
				int mpx = f->pos[0] + (f->pMod[0] * d[buttDir][0]);
				int mpy = f->pos[1] - (1-f->pMod[0]);
				int xd = d[buttDir][0];
				int yd = 1;	
				if (ep->dir % 2 == 0) {
					yd = d[buttDir][1];
					xd = 1;
					mpy = f->pos[1] + (f->pMod[1] * d[buttDir][1]);
					mpx = f->pos[0] - (1-f->pMod[1]);
				} 
				int xc = mpx + (((f->size[0]/2)+1) * xd);
				int yc = mpy + (((f->size[1]/2)+1) * yd);
				for (int x = 0; x < ep->xBite; x++) {
					for (int y = 0; y < ep->yBite; y++) {
						poo = removeFromStack(a);
						if (poo != NULL) {
							placeForm(xc -x, yc - y, poo);
						}else {
							x = 100;
							break;
						}
					}
				}
			} else {
				addToStack(poo, a);
			}
		}
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
