#define TYPE Form
//#include "World.h"

World *theWorld;

void makeWorld(int x, int y) {	

	World *newWorld = (World*)calloc(1, sizeof(World));
	TYPE ***mudBall = (TYPE***) calloc( x, sizeof(TYPE**));

	for (int i = 0; i < x ; i += 1) {
		mudBall[i] = (TYPE**) calloc( y , sizeof(TYPE*));
	}
	newWorld->map = mudBall;
	newWorld->x = x;
	newWorld->y = y;
	newWorld->terrain = makeList();
	theWorld = newWorld;
}

void deleteWorld() {
	for (int i = 0; i < theWorld->x ; i += 1) {
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
		next = t->next;
		deleteForm((Form*)t->data);
		free(t);
		t = next;
	}
}

void placeForm(int x, int y, TYPE *form) {
	form->pos[0] = x;
	form->pos[1] = y;
	theWorld->map[x][y] = form;
}

Form *removeForm(int x, int y) {
	Form *f = 0;
	if (x >= 0 && y >= 0 && x < theWorld->x && y < theWorld->y) {
		f = theWorld->map[x][y];
		theWorld->map[x][y] = 0;
	}
//	f->pos[0] = -1;
//	f->pos[1] = -1; maybe add back? took out because in the middle of move we need to remember the old position
	return f;
}

void dirtFloor(int height) {
	TYPE *d = makeDirt();
	addToList(theWorld->terrain, d);
	int maxGrow = 2;
	for (int x = 1; x < theWorld->x - 1; x++) {
		for(int y = 0; y < height; y++) {
			placeForm(x, y, d);
		}
		int newGrow = (int)(randPercent() * maxGrow);
		if (randPercent() > 0.5) {
			newGrow *= -1;
		}
		height = clamp(height + newGrow, 1, theWorld->y - 1);
		//printf("ng: %i, h: %i\n", newGrow, height);
	}
}

/*
int sumArr(int **array, int x, int y) {

	int sum = 0;

	for (int i = 0; i < x; i +=1) {
		for (int j = 0; j < y; j +=1) {
			sum +=array[i][j];
		}
	}

	return sum;
}

void showArr(int **array, int x, int y) {


	for (int i = 0; i < x; i +=1) {
		for (int j = 0; j < y; j +=1) {
			printf(" %i ", array[i][j]);
		}
		printf( "\n" );
	}
}
*/
