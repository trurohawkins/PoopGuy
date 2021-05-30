#ifndef LIB
#define LIB
#include "../helper/helper.h"
typedef struct Form {
	int pos[2];
	float color[3];
	int size[2];
	int ***body;
} Form;
//Form *inert;

Form *makeForm(float r, float g, float b, int wid, int len);
Form *checkSide(Form *f, int xd, int yd, bool collide);
void deleteForm(Form *f);
void makeInert();
Form *makeDirt();
int comparForms(Form *f1, Form *f2);

#include "../actor/Action.h"
#include "../actor/Actor.h"
#include "../actor/acts/control.h"
#include "World.h"
#include "FormGraphics.h"
#endif
