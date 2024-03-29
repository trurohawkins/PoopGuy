#define TYPE Form
#include "World.h"
World* theWorld;
#include "procGen.c"
#include "../actor/Eco.c"

void makeWorld(int x, int y) {	
	World *newWorld = (World*)calloc(1, sizeof(World));
	Cell ***mudBall = (Cell***) calloc( x, sizeof(Cell**));

	for (int i = 0; i < x ; i += 1) {
		mudBall[i] = (Cell**) calloc(y , sizeof(Cell*));
		for (int j = 0; j < y; j++) {
			mudBall[i][j] = makeCell(i,j);
		}
	}
	newWorld->map = mudBall;
	newWorld->x = x;
	newWorld->y = y;
	newWorld->terrain = makeList();
	theWorld = newWorld;
}

World *getWorld() {
	return theWorld;
}

void deleteWorld() {
	for (int i = 0; i < theWorld->x ; i += 1) {
		for (int j = 0; j < theWorld->y; j++) {
			/*
			Form *f = theWorld->map[i][j];
			if (f != NULL) {
				if (f->id == 10) {
					deleteForm(f);
				}
			}
			*/
		//	printCell(theWorld->map[i][j]);
			freeCell(theWorld->map[i][j]);
		}
		free(theWorld->map[i]); 
	}
	deleteTerrain();

	free(theWorld->map);
	free(theWorld);
}

void deleteTerrain() {
	linkedList *t = theWorld->terrain;
	linkedList *next;
	while (t != NULL) {
		printf("deleting\n");
		next = t->next;
		if (t->data != NULL) {
			deleteForm((Form*)t->data);
		}
		free(t);
		t = next;
	}
}

void placeForm(int x, int y, TYPE *form) {
	/*
	int mod[2] = {0,0};
	if (form->size[0] != 0 && form->size[1] != 0) {
		for (int i = 0; i < 2; i++) {
			if (form->size[i] % 2 == 0) {
				mod[i] = -0.5;
			}
		}
	}
	*/
	bool solidForm = checkFormIsSolid(form);
	form->pos[0] = x;// + mod[0];
	form->pos[1] = y;// + mod[1];
	if (form->size[0] == 0 && form->size[1] == 0) {
		if (x >= 0 && y >= 0 && x < theWorld->x && y < theWorld->y) {
			if (solidForm) {
				Form *f = getSolidForm(theWorld->map[x][y]);
				if (f != NULL) {
					deleteForm(f);
				}
			}
			//theWorld->map[x][y] = form;
			addToCell(theWorld->map[x][y], form);
		}
	} else {
		//printf("placing\n");
		for (int i = 0; i < form->size[0]; i++) {
			for (int j = 0; j < form->size[1]; j++) {
				int xp = form->pos[0] + form->body[i][j][0];
				int yp = form->pos[1] + form->body[i][j][1];
				if (xp >= 0 && yp >= 0 && xp < theWorld->x && yp < theWorld->y) {
					if (solidForm) {
						Form *f = getSolidForm(theWorld->map[xp][yp]);
						if (f != NULL) {
							deleteForm(f);
						}
					}
					addToCell(theWorld->map[xp][yp],form);
				}
			}
		}
	}
}

Form *checkForm(int x, int y) {
	return checkSolidForm(theWorld->map[x][y]);
}

Form *takeForm(int x, int y) {
	Form *form = 0;
	if (x >= 0 && y >= 0 && x < theWorld->x && y < theWorld->y) {
		/*
		form = theWorld->map[x][y];
		theWorld->map[x][y] = 0;
		*/
		form = getSolidForm(theWorld->map[x][y]);
	}
	return form;
}

Form *removeForm(Form* form) {
	if (form->size[0] == 0 && form->size[1] == 0) {
		int x = form->pos[0];
		int y = form->pos[1];
		if (x >= 0 && y >= 0 && x < theWorld->x && y < theWorld->y) {
		//takeForm(form->pos[0], form->pos[1]);
			removeFromCell(theWorld->map[x][y], form);
		}
	} else {
		for (int i = 0; i < form->size[0]; i++) {
			for (int j = 0; j < form->size[1]; j++) {
				int xp = form->pos[0] + (form->body[i][j])[0];
				int yp = form->pos[1] + (form->body[i][j])[1];
				/*
				if (xp >= 0 && yp >= 0 && xp < theWorld->x && yp < theWorld->y) {
					theWorld->map[xp][yp] = 0;
				}
				*/
				takeForm(xp, yp);
				//takeForm(form->pos[0], form->pos[1]);
			}
		}

	}

//	f->pos[0] = -1;
//	f->pos[1] = -1; maybe add back? took out because in the middle of move we need to remember the old position
	return form;
}

int getFormID(int x, int y) {
	if (x > -1 && y > -1 && x < theWorld->x && y < theWorld->y) {
		Form *f = checkSolidForm(theWorld->map[x][y]);
		if (f != NULL) {
			return f->id;
		}
	}
	return -1;
}

void freeWorld() {
	deleteActorList();
	deleteWorld();
	freeDirections();
}

Form *makeDirt(int moist) {
	Form *d = makeForm(0.7, 0.3, 0.1, 1, 1);
	d->id = 1 * getRecipePow();
	int cPow = (moist / getRecipePow()) * getRecipePow();
	float mVal = moist - cPow;
	addStat(d, "moisture", mVal * 0.1);
	addStat(d, "hydroK", 1);
	float tileVal = 0 + randPercent();//randpercent used as remainer to determine which tile to use for this block
	addStat(d, "tile", tileVal);//or anim
	//addToList(&(theWorld->terrain), d);
	return d; //makeForm(0.7, 0.3, 0.1, 0, 0);
}

int saveDirt(Form *d) {
	int id = d->id;
	id = clamp(id += *getStat(d, "moisture") * 10, 10, 19);
	//printf("dirt w/%f becomes %i\n", *getStat(d,"moisture"), id);
	return id;
}

Form *makeStone(int null) {
	Form *s = makeForm(0.2, 0.3, 0.4, 1, 1);
	s->id = 2 * getRecipePow();
	addStat(s, "moisture", 0);
	addStat(s, "hydroK", 1);
	addStat(s, "tile", 1);//or anim
	//addToList(&(theWorld->terrain), d);
	return s; //makeForm(0.7, 0.3, 0.1, 0, 0);
}

int saveForm(Form *f) {
	//printf("saving form\n");
	return f->id;
}

void makeInert() {
	inert = makeForm(0,0,0, 0, 0);
	inert->pos[0] = -1;
	inert->pos[1] = -1;
}

// make Square fun
// x,y are starting point of square, z is side length
// goes clock wise 
// STAUS: runtime error? not showing up in game world
// no complier erros (So not syntax error?)
//

void makeSquare(int x, int y, int z) {
	float moist = 0;
	TYPE *b = makeDirt(moist) ;
	//addToList(&(theWorld->terrain), b);
	for (int i = 1; i < z ; i++) {
		for (int j = 1; j < z ; j++) {
			placeForm( x + i, y + j, b) ;
		}
	}
}

void makeStoneSquare(int x, int y, int z) {
	//addToList(&(theWorld->terrain), b);
	for (int i = 1; i < z ; i++) {
		for (int j = 1; j < z ; j++) {
			TYPE *b = makeStone(0) ;
			placeForm( x + i, y + j, b) ;
		}
	}
}

 void makeCircle(int x, int y, int r) {
	//printf("making circle ");
	float moist = 0;
	TYPE *b = makeDirt(moist) ;
	//addToList(&(theWorld->terrain), b);
	int sx = x - r ;
	int sy = y - r ;
	int test ;
	int xd ;
	int yd ;
	//printf(" starting at (%i, %i) ", sx, sy);
	for (int i = sx; i < ( sx + (2*r)+1 ) ; i++) {
		for (int j = sy; j < ( sy + (2*r)+1 ); j++) {
		  xd = (x-i);
		  yd = (y-j);	  
		  if ( sqrt ( (xd * xd) + (yd *yd) )  <= r )  {
	   	test =  (sqrt( (xd * xd) + (yd *yd) )) ;  	
		   //printf(" d=%i ", test) ;
		    placeForm(i, j, b) ;
		    //printf(" (%i, %i) ", i, j);

}}}}

void dirtFloor(int height) {
	float moist = 0;
	TYPE *d = makeDirt(moist);
	//addToList(&(theWorld->terrain), d);
	int maxGrow = 6;
	for (int x = 0; x < theWorld->x; x++) {
		for(int y = 0; y < height; y++) {
			placeForm(x, y, d);
		}
		if (randPercent() > 0.75) {
			int newGrow = (int)(randPercent() * maxGrow);
			if (randPercent() > 0.5) {
				newGrow *= -1;
			}
			height = clamp(height + newGrow, 1, theWorld->y - 1);
		}
		//printf("ng: %i, h: %i\n", newGrow, height);
	}
}

void writeWorld(char *file) {
	//resets file to overwrite previous data
	int xs = theWorld->x;
	int ys = theWorld->y;
	FILE *fptr = fopen(file, "wb");
	int sizes[2] = {xs, ys};
	fwrite(sizes, sizeof(int), 2, fptr);
	fclose(fptr);	
	
	int count = 0;
	for (int x = 0; x < xs; x++) {
		for (int y = 0; y < ys; y++) {
			Cell *cur = theWorld->map[x][y];
			if (cur->count > 0) {
				if (writeCell(file, cur)) {
					count++;
				}
			}
		}
	}
	//loadWorld(file);
}

bool loadWorld(char *file) {
	FILE *fptr = fopen(file, "rb");
	if (fptr != NULL) {
		int *size = readBinaryInt(fptr, 2);
		makeWorld(size[0], size[1]);
		int *cellCount = (int*)calloc(sizeof(int), 1);
		//for (int i = 0; i < count; i++) {
		while (fread(cellCount, sizeof(int), 1, fptr) > 0) {
			//int *cellCount = readBinaryInt(fptr, 1);
			int *pos = readBinaryInt(fptr, 2);
			int *residents = readBinaryInt(fptr, *cellCount);
			Cell *cur = theWorld->map[pos[0]][pos[1]];

			for (int j = 0; j < *cellCount; j++) {
				if (residents[j] < 10) {
					printf("cell at %i, %i, count = %i: ", pos[0], pos[1], *cellCount);
					printf("%i, \n", residents[j]);
				}
				FormRecipe *r = getRecipe(residents[j]);
				if (r) {
					placeForm(pos[0], pos[1], r->makeFunc(residents[j]));
				}
				/*
				if (residents[j] == 10) {
					//addToCell(cur, makeDirt(0));
					placeForm(pos[0], pos[1], makeDirt(0));
				}
				*/
			}
			free(pos);
			free(residents);
		}
		free(cellCount);
		fclose(fptr);
		return true;
	}
	return false;
}
