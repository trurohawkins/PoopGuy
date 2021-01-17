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

#include "../helper.c"
#include "World.c"
#include "../actor/Action.c"
#include "../actor/Actor.c"
#include "FormGraphics.c"
