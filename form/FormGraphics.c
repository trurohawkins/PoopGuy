#include "../graphicsSource/Graphics.h"
#include<stdio.h>

void drawForm(Form *f, int x, int y, int size) {
	if (f != 0) {
		printf("%f /n", f->color[0]);
		drawSquare(f->color, x, y, size);
	}
}


void drawWorld(World *world) {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i=0; i < world->x ; i ++) {
		for (int j=0; j < world->x; j++){
			drawForm( &(world->map[i][j]), i, j, 1);
		}
	}
	//&(world->map[0][0]);
	//(world->map[0]) + 0;
	// drawForm(world->map[0][0], 0, 0, 1);	
	
	glutSwapBuffers();
}

void drawFunc(Form **world, int x, int y) {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	Form *f = makeForm(1, 1, 1);
	drawForm(f, 0, 0, 1);	
	free(f);
	
	glutSwapBuffers();
}


