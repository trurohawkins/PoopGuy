#include "Form.h"
Form *inert;
Form *makeForm(float r, float g, float b) {
	Form *newForm = (Form *)calloc(1, sizeof(Form));
	newForm->pos[0] = -1;
	newForm->pos[1] = -1;
	newForm->color[0] = r;
	newForm->color[1] = g;
	newForm->color[2] = b;
	return newForm;
}

void deleteForm(Form *f) {
	free(f);
}

Form *makeDirt() {
	return makeForm(0.7, 0.3, 0.1);
}

void makeInert() {
	inert = makeForm(0,0,0);
	inert->pos[0] = -1;
	inert->pos[1] = -1;
}

int compareForms(Form *f1, Form *f2) {
	if (f1->color[0] == f2->color[0] && f1->color[1] == f2->color[1] && f1->color[2] == f2->color[2]) {
		return 1;
	} else {
		return 0;
	}
}

//#include "../helper/helper.c"
#include "World.c"
#include "../actor/Action.c"
#include "../actor/Actor.c"
#include "../actor/acts/control.c"
#include "FormGraphics.c"
