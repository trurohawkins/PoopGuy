#include "../graphicsSource/Graphics.c"

//#include<stdio.h>

void drawForm(Form *f, int x, int y, int size) {
	if (f != 0) {
		//	printf("%i, %i is %f \n", x, y, f->color[0]);
			drawSquare(f->color, x, y, size);
	}
}
int centerX;
int centerY;

void drawWorld() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	int fx = frameX/2;
	int fy = frameY/2;
	int cx = clamp(centerX, fx, theWorld->x - fx);
	int cy = clamp(centerY, fy, theWorld->y - fy);
	for (int i=cx-fx; i <= cx+fx ; i ++) {
		for (int j=cy-fy; j <= cy+fy; j++){
			if (i >= 0 && i < theWorld->x && j >= 0 && j < theWorld->y) {
				drawForm( theWorld->map[i][j], i-(cx-fx), j-(cy-fy), 1);
			}
		}
	}
	
	glutSwapBuffers();
}

void setCenter(int cp[2]) {
	centerX = cp[0];
	centerY = cp[1];
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


