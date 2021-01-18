#include "helper.h"
#include "list.c"
int **dirs;

void initDirections() {
	dirs = (int**)calloc(4, sizeof(int*));
	for (int i = 0; i < 4; i++) {
		dirs[i] = (int*)calloc(2, sizeof(int));
	}
	dirs[0][0] = 0;
	dirs[0][1] = 1;
	dirs[1][0] = -1;
	dirs[1][1] = 0;
	dirs[2][0] = 0;
	dirs[2][1] = -1;
	dirs[3][0] = 1;
	dirs[3][1] = 0;
}

void freeDirections() {
	for (int i = 0; i < 4; i++) {
		free(dirs[i]);
	}
	free(dirs);
}

float randPercent() {
	return (float)rand()/(float)(RAND_MAX);
}

int clamp(int val, int min, int max) {
	if (min < max) {
		if (val < min) {
			return min;
		}	else if (val > max) {
			return max;
		} else {
			return val;
		}
	} else {
		return val;
	}
}

int sign(int num) {
	if (num > 0) {
		return 1;
	} else if (num < 0) {
		return -1;
	} else {
		return 0;
	}
}

int abs(int num) {
	if (num < 0) {
		return num * -1;
	} else {
		return num;
	}
}
