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
	form->pos[0] = x;// + mod[0];
	form->pos[1] = y;// + mod[1];
	if (form->size[0] == 0 && form->size[1] == 0) {
		if (x >= 0 && y >= 0 && x < theWorld->x && y < theWorld->y) {
			theWorld->map[x][y] = form;
		}
	} else {
		//printf("placing\n");
		for (int i = 0; i < form->size[0]; i++) {
			for (int j = 0; j < form->size[1]; j++) {
				int xp = form->pos[0] + form->body[i][j][0];
				int yp = form->pos[1] + form->body[i][j][1];
				if (xp >= 0 && yp >= 0 && xp < theWorld->x && yp < theWorld->y) {
					//printf("placing: %i, %i\n", xp, yp);
					theWorld->map[xp][yp] = form;
				}
			}
		}
	}
}

Form *takeForm(int x, int y) {
	Form *form = 0;
	if (x >= 0 && y >= 0 && x < theWorld->x && y < theWorld->y) {
		form = theWorld->map[x][y];
		theWorld->map[x][y] = 0;
	}
	return form;
}

Form *removeForm(Form* form) {
	if (form->size[0] == 0 && form->size[1] == 0) {
		takeForm(form->pos[0], form->pos[1]);
	} else {
		for (int i = 0; i < form->size[0]; i++) {
			for (int j = 0; j < form->size[1]; j++) {
				int xp = form->pos[0] + form->body[i][j][0];
				int yp = form->pos[1] + form->body[i][j][1];
				if (xp >= 0 && yp >= 0 && xp < theWorld->x && yp < theWorld->y) {
					theWorld->map[xp][yp] = 0;
				}
			}
		}

	}

//	f->pos[0] = -1;
//	f->pos[1] = -1; maybe add back? took out because in the middle of move we need to remember the old position
	return form;
}

// make Square fun
// x,y are starting point of square, z is side length
// goes clock wise 
// STAUS: runtime error? not showing up in game world
// no complier erros (So not syntax error?)
//

void makeSquare(int x, int y, int z) {
	TYPE *b = makeDirt() ;
//	addToList(theWorld->terrain, b);
	for (int i = 1; i < z ; i++) {
		for (int j = 1; j < z ; j++) {
			placeForm( x + i, y + j, b) ;
		}
	}

}
void dirtFloor(int height) {
	TYPE *d = makeDirt();
	addToList(theWorld->terrain, d);
	int maxGrow = 2;
	for (int x = 1; x < theWorld->x - 1; x++) {
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
