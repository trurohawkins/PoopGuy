#ifndef LIB
#define LIB
#include "../helper/helper.h"
typedef struct Form {
	int id;
	float pos[2];
	float pMod[2];
	float color[3];
	int size[2];
	int roto;
	bool invert[2];
	float ***body;
	void *anim;
	float stat;
	void *stats;
} Form;
//Form *inert;

Form *makeForm(float r, float g, float b, float wid, float len);
Form *checkSide(Form *f, int xd, int yd, bool collide);
int getEdge (Form *f, int side, int d);
void deleteForm(Form *f);
void makeInert();
int compareForms(Form *f1, Form *f2);
void setRoto(Form *f, int degree);
void setInvert(Form *f, int axis, bool flipped);
//void setStat(Form *f, float stat);
void freeWorld();

#include "../actor/Action.h"
#include "../actor/Actor.h"
#include "../actor/acts/control.h"
#include "World.h"
#include "Value.h"
#endif
