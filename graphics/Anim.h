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
	int drawOrder;
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
	float offset[2];
	int roto;
	textureSource *texture;
	float *palette;
	unsigned int vao;
} Anim;

#include "AnimList.h"
#include "UI.h"

Anim *makeAnim(char **sheet, int spriteNum, bool generated, int rows, int col);
unsigned int makeSpriteTexture(char *sheet, int rows, int col);
void getUniformValue(GLuint texShader, char *name, GLuint *dest);
void setTexTrans(GLuint tt);
void setTexScale(GLuint ts);
void setTexColor(GLuint tc);
void initTexInts(GLuint texShader);
float rotoToRadian(int d);
void freeAnim(Anim *a);
void setScale (Anim* a, int x, int y);
void setOffset (Anim* a, float x, float y);
void setFlipX(Anim *a, int x);
void setFlipY(Anim *a, int y);
void setRotation(Anim *a, int d);
void setDrawOrder(Anim *a, int o);
void addSprite(Anim *a, int index, int len);
void animAddVao(Anim *a, GLuint vao);
void animate(Anim *a);
void changeSprite(Anim *a, int index);
float getCoordX(Anim *a);
float getCoordY(Anim *a);
void setSpriteTexture(Anim *a);
void drawSprite(Anim *a);
void loadPalette(Anim *a, float *palette);

#endif
