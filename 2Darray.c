#include<stdlib.h>
#include<stdio.h>


int **makeWorld(int x, int y) {
	


	int **Mudball = (int**) calloc( x, sizeof(int*));

	for (int i = 0; i < x ; i += 1) {
		Mudball[i] = (int*) calloc( y , sizeof(int));
	}
	return Mudball;
}

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

void deleteWorld(int **array, int x) {

	
	for (int i = 0; i < x ; i += 1) {
		free(array[i]); 
	}

	free(array);
}
