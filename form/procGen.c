#include <stdio.h>
#include <math.h>
#include "../helper/helper.c"
// #include "procGen.h"

void arrayToFile(char *txt, int **array)
{
	FILE *fptr;

    int sizeX = theWorld->x;
    int sizeY = theWorld->y;

	fptr = fopen(txt, "w");

	if (fptr != NULL) {
		fwrite(array, sizeof(int), sizeX*sizeY, fptr);
	}
		fseek(fptr, 0, SEEK_SET);
		fclose(fptr);
}


int **fileToArray(char *txt) {
	FILE *fptr;

  int sizeX = theWorld->x;
  int sizeY = theWorld->y;

	int **array = (int**) calloc( sizeX, sizeof(int*));
  for (int i = 0; i < sizeX ; i += 1) {
			array[i] = (int*) calloc( sizeY , sizeof(int));
	}

	fptr = fopen(txt, "r");

	if (fptr != NULL) {
		fread(array, sizeof(int), sizeX*sizeY, fptr);	
		fseek(fptr, 0, SEEK_SET);
		fclose(fptr);
	}
	return array;
}
int** genMap(int *Seedstringd) {
    // Declare map array
    int sizeX = theWorld->x;
    int sizeY = theWorld->y;
    
    //int map[sizeX][sizeY];
    // int map[theWolrd->x][theWolrd->y]
    // using global Variables
    int **map = (int**) calloc( sizeX, sizeof(int*));

    for (int i = 0; i < sizeX ; i += 1) {
			map[i] = (int*) calloc( sizeY , sizeof(int));
		}
    // Variables for block flags
    int space = 0;
    int dirt = 10;
    //int basalt = 90
    
    // Intialize map with space
    for (int x = 0; x < sizeX; x++) {
        	for(int y = 0; y < sizeY; y++) {
        	    map[x][y] = space;
        	}
    }
    
    // parse out Seed String into interger vector
    
    int maxGrow = sizeY/3;
    int height = sizeY/5;
		for (int x = 0; x < sizeX; x++) {
			for(int y = 0; y < height; y++) {
		// this should write flag to array
	    	map[x][y] = dirt ;
			}
			if (randPercent() > 0.75) {
				int newGrow = (int)(randPercent() * maxGrow);
				// printf( "%f \n", randPercent());
				if (randPercent() > 0.5) {
					newGrow *= -1;
				}
				height = clamp(height + newGrow, 1, sizeY - sizeY/5);
			}
		}
	return map;
}

void freeMap(int **map) {
	int sx = theWorld->x;
	int sy = theWorld->y;
	for (int i = 0; i < sx; i++) {
		free(map[i]);
	}
	free(map);
}

int** genRain( int **map) {
    int sizeX = theWorld->x;
    int sizeY = theWorld->y;
	int blocksum;

	int satVal = 9;
	int inc = 11;

	for (int x =0; x < sizeX; x++) {
		blocksum = 0;
		for(int y= sizeY-1; y > 0; y--) {
			blocksum = blocksum + map[x][y+1];
			if (map[x][y] = 10) && (blocksum = 0) {
				map[x][y] = map[x][y] + satVal;
			} 	
			if (map[x][y] = 10) && (map[x][y+1] > 10) {
				map[x][y] = map[x][y] + ( map[x][y+1] - inc);
			}
		}
	}
	return map;
}

void genWorld(int **map) {
	float moist;
	for (int x = 0; x < theWorld->x; x++) {
		for(int y = 0; y < theWorld->y; y++) {
			if ( map[x][y] > 0 ) {
				moist = map[x][y] - 10;
				TYPE *d = makeDirt();
				placeForm(x, y, d);
			} 
		}
	}	
}
