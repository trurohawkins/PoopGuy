#include "Cell.h"

Cell *makeCell(int x, int y) {
	Cell *c = (Cell*)calloc(sizeof(Cell), 1);
	c->pos[0] = x;
	c->pos[1] = y;
	c->within = 0;//makeList();
	c->count = 0;
}

void addToCell(Cell* c, Form *f) {
	if (f != NULL) {
		/*
		if (c->within == 0) {
			c->within = makeList();
		}
		*/
		addToList(&(c->within), f);
		c->count++;
		if (c->count > 1) {
			printf("why so many in here??\n");
			printCell(c);
		}
		//if (f->size[0] != 0 && f->size[1] != 0) {
		if (checkFormIsSolid(f)) {
			c->solid = true;
		}
	} else {
		printf("tried to add NULL form to Cell ");
		printCell(c);
	}
}

Form *getSolidForm(Cell* c) {
	Form *f = 0;
	if (c->within != 0) {
		//printCell(c);
		f = removeFromListCheck(&(c->within), checkFormIsSolid);	
		//printCell(c);
		c->count--;
		c->solid = false;
	}
	return f;
}

Form *checkSolidForm(Cell* c) {
	//printf("check cell for solid 
	Form *f = 0;
	//if (c->solid) {
	if (c->within != 0) {
		f = (Form*)checkList(&(c->within), checkFormIsSolid);	
	}
	return f;
}

Form **getContents(Cell *c) {
	if (c->count == 0 || c->within == NULL) {
		return NULL;
	}
	Form **content = (Form**)calloc(sizeof(Form*), c->count);
	linkedList *cur = c->within;
	int count = 0;
	while (cur != NULL) {
		if (cur->data != NULL) {
			content[count] = (Form*)cur->data;
			count++;
		}
		cur = cur->next;
	}
	return content;
}

void printCell(Cell *c) {
	printf("printing Cell %i, %i\n", c->pos[0], c->pos[1]);
	if (c->within != 0) {
		printList(&(c->within), "within", printForm);
	}
}

void freeCell(Cell *c) {
	if (c->within != 0) {
		deleteList(&(c->within), deleteForm);
	}
	free(c);
}
