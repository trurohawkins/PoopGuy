#include "../graphicsSource/Graphics.c"

//#include<stdio.h>

void drawForm(Form *f, int x, int y, int size) {
	if (f != 0) {
		//	printf("%i, %i is %f \n", x, y, f->color[0]);
			drawSquare(f->color, x, y, size);
	}
}
bool grid = false;
float centerX;
float centerY;

void drawWorld() {
	glClearColor(0.1, 0.2, 0.75, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	int fx = frameX/2;
	int fy = frameY/2;
	int cx = clamp(centerX, fx, theWorld->x - fx - 1);
	int cy = clamp(centerY, fy, theWorld->y - fy - 1);
	for (int i=cx-fx; i <= cx+fx ; i ++) {
		for (int j=cy-fy; j <= cy+fy; j++){
			if (i >= 0 && i < theWorld->x && j >= 0 && j < theWorld->y) {
				drawForm( theWorld->map[i][j], i-(cx-fx), j-(cy-fy), 1);
			}
		}
	}
	if (grid) {
		for (int i=cx-fx; i <= cx+fx ; i ++) {
			for (int j=cy-fy; j <= cy+fy; j++){
				drawLine(0,0,0,0, j-(cy-fy), frameX, j-(cy-fy));
			}
			drawLine(0,0,0,i-(cx-fx), 0, i-(cx-fx), frameY);
		}
	}
			
			glutSwapBuffers();
}

void setCenter(float cp[2]) {
	centerX = cp[0];
	centerY = cp[1];
}

void setGrid(bool on) {
	grid = on;
}
/*
void drawFunc() {
	printf("caca\n");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	Form *f = makeForm(1, 1, 1);
	drawForm(f, 0, 0, 1);	
	free(f);
	
	glutSwapBuffers();
}

*/
