#include "Form.h"
Form *inert;
Form *makeForm(float r, float g, float b, float wid, float len) {
	Form *newForm = (Form *)calloc(1, sizeof(Form));
	newForm->id = -1;
	newForm->pos[0] = -1;
	newForm->pos[1] = -1;
	newForm->color[0] = r;
	newForm->color[1] = g;
	newForm->color[2] = b;
	newForm->size[0] = wid;
	newForm->size[1] = len;
	newForm->anim = 0;
	//newForm->roto = 0;
	//newForm->invert[0] = false;
	//newForm->invert[1] = false;
	if ((int)wid % 2 == 0) {
		newForm->pMod[0] = -0.5;
	} else {
		newForm->pMod[0] = 0;
	}
	if ((int)len % 2 == 0) {
		newForm->pMod[1] = -0.5;
	} else {
		newForm->pMod[1] = 0;
	}
	//float wid = w;
	//float len = l;
	if (wid != 0 && len != 0) {
		//printf("form with body\n");
		newForm->body = (float***) calloc(wid, sizeof(float**));
		for (int i = 0; i < wid; i++) {
			newForm->body[i] = (float**) calloc(len, sizeof(float*));
		}
		wid -= 1;
		len -= 1;	
		for (int x = 0; x <= wid; x++) {
			for(int y = 0; y <= len; y++) {
				newForm->body[x][y] = (float*)calloc(2, sizeof(float));
				newForm->body[x][y][0] = -(wid/2) + x;
				newForm->body[x][y][1] = -(len/2) + y;
				float xb = -(wid/2) + x;
				float yb = -(len/2) + y;
				//printf("[%i][%i] = %f, %f\n", x, y, newForm->body[x][y][0], newForm->body[x][y][1]);
				//printf("float val = %f, %f\n", xb, yb);
			}
		}
	} else {
		//printf("no body on this form\n");
		newForm->body = 0;
	}
	return newForm;
}

int getEdge(Form *f, int side, int d) {
	if (d > 0) {
		return f->pos[side]+(int)(f->size[side]+f->pMod[side])/2 + 1;
	} else {
		return f->pos[side]-(int)(((f->size[side]-f->pMod[side])/2 + 1)); 
	}
}

Form *checkSide(Form *f, int xd, int yd, bool collide) {
	Form *hit =0;
	if (xd != 0) {
		int col = 0;
		if (xd > 0) {
			col = (f->size[0]+f->pMod[0])/2 + 1;
		} else if (xd < 0) {
			col = -((f->size[0]-f->pMod[0])/2 + 1);
		}
		int hei = f->size[1];//(f->size[1]-f->pMod[1])/2;
		//printf("hei: %i - from %f\n", hei, f->size[1] + f->pMod[1]);
		if (collide) {
			//printf("checking side, Im at %f, %f\n", f->pos[0], f->pos[1]);
		}
		for (int i = 0; i < hei; i++) {
			//if (collide) {
			//	printf("p: %f, %f\n", f->pos[0] + col, (f->pos[1] - f->size[1]/2) + i);
			//}
			hit = checkCol(f->pos[0] + col, (f->pos[1] - f->size[1]/2) + i);
			if (hit != 0) {
				break;
			}
		}
		if (hit != 0) {
			//printf("hit something X\n");
			return hit;
		}
	}
	if (yd != 0) {
		int row = 0;
		if (yd > 0) {
			row = (f->size[1]+f->pMod[1])/2 + 1;
		} else if (yd < 0) {
			row = -((f->size[1]-f->pMod[1])/2 + 1);
		}
		int wid = f->size[0];///2;
		//printf("checking side, Im at %f, %f\n", f->pos[0], f->pos[1]);
		for (int i = 0; i < wid; i++) {
			//printf("checking: %f, %f\n", (f->pos[0] - f->size[0]/2) + i, f->pos[1] + row);
			hit = checkCol((f->pos[0] - f->size[0]/2) + i, f->pos[1] + row);
			if (hit != 0) {
				break;
				//printf("hit something Y\n");
			}
		}
	}
	return hit;
}


void deleteForm(void *form) {
	Form *f = (Form*)form;
	//removeForm(f);
//	printf("form: %i\n", f->id);
	if (f->size[0] != 0 && f->size[1] != 0) {
		for (int x = 0; x < f->size[0]; x++) {
			for(int y = 0; y < f->size[1]; y++) {
				free(f->body[x][y]);
			}
		}
		for (int i = 0; i < f->size[0]; i++) {
			free(f->body[i]);
		}
	}
	if (f->stats != NULL) {
		deleteList((linkedList**)&f->stats, freeValue);
	}
	free(f->body);
	free(f);
}


bool compareForms(Form *f1, Form *f2) {
	return f1 == f2;
	if (f1->color[0] == f2->color[0] && f1->color[1] == f2->color[1] && f1->color[2] == f2->color[2]) {
		return 1;
	} else {
		return 0;
	}
}
/*
void setRoto(Form *f, int degree) {
	f->roto = degree;
}

void setInvert(Form *f, int axis, bool flipped) {
	f->invert[axis] = flipped;
}
*/
bool checkFormIsSolid(void *form) {
	Form *f = (Form*)form;
	if (f->size[0] != 0 || f->size[1] != 0) {
		return true;
	} else {
		return false;
	}
}

bool isFormCenter(Form *f, int x, int y) {
	//if (f->size[0] <= 1 && f->size[1] <= 1) {
	if ((int)floor(f->pos[0]) == x && (int)floor(f->pos[1] == y)) {
		return true;
	} else {
		return false;
	}
}

void printForm(void *form) {
	Form *f = (Form*)form;
	printf("form id: %i size:%i, %i\n", f->id, f->size[0], f->size[1]);
}

/*
void setStat(Form *f, float stat) {
	//printf("setting stat %f\n", stat);
	f->stat = stat;
}
*/


//#include "../helper/helper.c"
#include "World.c"
#include "Value.c"
#include "Cell.c"
#include "FormSpawner.c"
#include "../actor/Action.c"
#include "../actor/Actor.c"
#include "../actor/acts/control.c"
