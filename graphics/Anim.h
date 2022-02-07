#ifndef ANIM
#define ANIM
#include "glfwMain.h"
//#include <stdio.h>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <GL/gl.h>
#include <stdbool.h>
#include "../helper/helper.h"
#include "TextureManager.h"


typedef struct Anim {
	int speed;
	int speedCounter;
	float frameX;
	float frameY;
	int frame;
	int sprite;
	int spriteNum;
	int *length;
	int scale[2];
	int flip[2];
	int roto;
	GLuint texCoords;
	GLuint texScale;
	textureSource *texture;
	float *palette;
	unsigned int vao;
} Anim;

#include "AnimList.h"

Anim *makeAnim(char *sheet, int rows, int col, GLuint tc, GLuint ts);
unsigned int makeSpriteTexture(char *sheet, int rows, int col);
float rotoToRadian(int d);
void freeAnim(Anim *a);
void setScale (Anim* a, int x, int y);
void setFlipX(Anim *a, int x);
void setFlipY(Anim *a, int y);
void setRotation(Anim *a, int d);
void addSprite(Anim *a, int index, int len);
void animAddVao(Anim *a, GLuint vao);
void animate(Anim *a);
void changeSprite(Anim *a, int index);
float getCoordX(Anim *a);
float getCoordY(Anim *a);
void setSpriteTexture(Anim *a);
void drawSprite(Anim *a, GLuint texColor);
void loadPalette(Anim *a, float *palette);

#endif
