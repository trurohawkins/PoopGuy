#include "GL/freeglut.h"
#include "GL/gl.h"

void initializeGLUT(int argc, char **argv, int winSX, int winSY, int worldX, int worldY) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(winSX, winSY);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("poop guy");
	glOrtho(0, worldX, 0, worldY, -1.0, 1.0);	
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
