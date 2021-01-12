#include <stdio.h>
#include <unistd.h>
#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif
#include "form/FormGraphics.h"

int main(int argc, char **argv) {
	int worldX = 10;
	int worldY = 10;
	int windowX = 500;
	int windowY = 500;
	initializeGLUT(argc, argv, windowX, windowY, worldX, worldY);
	glutDisplayFunc(drawFunc);
	glutMainLoop();
}
