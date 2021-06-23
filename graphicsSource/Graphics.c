#include "GL/freeglut.h"
//#include "GL/gl.h"

int frameX=75;
int frameY=75;

void initializeGLUT(int argc, char **argv, int winSX, int winSY) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(winSX, winSY);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("poop guy");
	glOrtho(0, frameX, 0, frameY, -1.0, 1.0);	
}

void drawSquare(float *color, int x, int y, int size) {
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, y, 0);
		glVertex3f(x + size, y, 0);
		glVertex3f(x + size, y + size, 0);
		glVertex3f(x + size, y + size, 0);
		glVertex3f(x, y + size, 0);
		glVertex3f(x, y, 0);
	glEnd();
}

void drawLine(float r, float g, float b, int x1, int y1, int x2, int y2) {
	glColor3f(r, g, b);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}
