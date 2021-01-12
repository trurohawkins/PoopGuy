#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

typedef struct Form
{
	float color[3];
} Form;

Form *makeForm(float r, float g, float b) {
	Form *newForm = (Form *)calloc(1, sizeof(Form));
	newForm->color[0] = r;
	newForm->color[1] = g;
	newForm->color[2] = b;
	return newForm;
}
