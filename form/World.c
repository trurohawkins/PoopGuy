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
	theWorld = newWorld;
}

void deleteWorld() {
	for (int i = 0; i < theWorld->x ; i += 1) {
		free(theWorld->map[i]); 
	}

	free(theWorld->map);
	free(theWorld);
}

void placeForm(int x, int y, TYPE *form) {
	form->pos[0] = x;
	form->pos[1] = y;
	theWorld->map[x][y] = form;
}

Form *removeForm(int x, int y) {
	Form *f = theWorld->map[x][y];
	theWorld->map[x][y] = 0;
	f->pos[0] = -1;
	f->pos[1] = -1;
	return f;
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
