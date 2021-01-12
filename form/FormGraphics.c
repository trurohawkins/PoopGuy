#include "Form.c"
#include "../graphicsSource/Graphics.c"

void drawForm(Form * f, int x, int y, int size) {
	drawSquare(f->color, x, y, size);
}

void drawFunc() {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	Form *f = makeForm(1, 1, 1);
	drawForm(f, 0, 0, 1);	
	free(f);
	glutSwapBuffers();
}

