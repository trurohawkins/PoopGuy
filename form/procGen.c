#include <stdio.h>
#include <math.h>
#include "../helper/helper.c"
// #include "procGen.h"


int** mapGen(int *Seedstring, int WorldX, int WorldY) {
    // Declare map array
    int sizeX = WorldX;
    int sizeY = WorldY;
    
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
			printf( "%f \n", randPercent());
			if (randPercent() > 0.5) {
				newGrow *= -1;
			}
			height = clamp(height + newGrow, 1, sizeY - sizeY/5);
		}
    
	}
	return map;
}