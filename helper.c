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
