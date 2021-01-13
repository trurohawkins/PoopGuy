#define TYPE Form

World *makeWorld(int x, int y) {	

	World *newWorld = (World*)calloc(1, sizeof(World));
	TYPE **mudBall = (TYPE**) calloc( x, sizeof(TYPE*));

	for (int i = 0; i < x ; i += 1) {
		mudBall[i] = (TYPE*) calloc( y , sizeof(TYPE));
	}
	newWorld->map = mudBall;
	newWorld->x = x;
	newWorld->y = y;
	return newWorld;
}
void deleteWorld(World *world) {

	
	for (int i = 0; i < world->x ; i += 1) {
		free(world->map[i]); 
	}

	free(world->map);
	free(world);
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
