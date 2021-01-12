#include<stdlib.h>
#include<stdio.h>


int **arrayA(int x, int y) {
	


	int **Mudball = (int**) calloc( x, sizeof(int*));

	for (int i = 0; i < x ; i += 1) {
		Mudball[i] = (int*) calloc( y , sizeof(int));
	}
	return Mudball;
}

int sumA(int **array, int x, int y) {

	int sum = 0;

	for (int i = 0; i < x; i +=1) {
		for (int j = 0; j < y; j +=1) {
			sum +=array[i][j];
		}
	}

	return sum;
}

void showA(int **array, int x, int y) {


	for (int i = 0; i < x; i +=1) {
		for (int j = 0; j < y; j +=1) {
			printf(" %i ", array[i][j]);
		}
		printf( "\n" );
	}
}
