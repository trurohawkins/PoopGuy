#ifndef LIB
#define LIB
#include "../helper/helper.h"
typedef struct Form {
	int id;
	float pos[2];
	float pMod[2];
	float color[3];
	int size[2];
	float ***body;
	void *anim;
} Form;
//Form *inert;

Form *makeForm(float r, float g, float b, float wid, float len);
Form *checkSide(Form *f, int xd, int yd, bool collide);
int getEdge (Form *f, int side, int d);
void deleteForm(Form *f);
void makeInert();
int compareForms(Form *f1, Form *f2);
void setAnim(Form *f, void *a);
void freeWorld();

#include "../actor/Action.h"
#include "../actor/Actor.h"
#include "../actor/acts/control.h"
#include "World.h"
//#include "FormGraphics.h"
#endif
