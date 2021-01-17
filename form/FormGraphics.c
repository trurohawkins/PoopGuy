#include "../graphicsSource/Graphics.h"
#include<stdio.h>

void drawForm(Form *f, int x, int y, int size) {
	if (f != 0) {
	//	printf("%i, %i is %f \n", x, y, f->color[0]);
		drawSquare(f->color, x, y, size);
	}
}


void drawWorld() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i=0; i < theWorld->x ; i ++) {
		for (int j=0; j < theWorld->x; j++){
			drawForm( theWorld->map[i][j], i, j, 1);
		}
	}
	//&(theWorld->map[0][0]);
	//(theWorld->map[0]) + 0;
	// drawForm(theWorld->map[0][0], 0, 0, 1);	
	
	glutSwapBuffers();
}

void drawFunc() {
	printf("caca\n");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	Form *f = makeForm(1, 1, 1);
	drawForm(f, 0, 0, 1);	
	free(f);
	
	glutSwapBuffers();
}


