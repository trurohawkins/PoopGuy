#ifndef GHOST
#define GHOST

typedef struct Ghost {
	float xp;
	float yp;
	float xSize;
	float ySize;
	bool xInvert;
	bool yInvert;
	int roto;
	Anim *a;
} Ghost;

void initBackgroundGhosts();
void addBackground(Ghost *gho); 
void drawBG(float *sMatrix, GLuint sScale, GLuint sTrans, GLuint sRot, GLuint texColor);
void freeBG();
void initForegroundGhosts();
void addForeground(Ghost *gho); 
void drawFG(float *sMatrix, GLuint sScale, GLuint sTrans, GLuint sRot, GLuint texColor);
void freeFG();
void drawGround(linkedList *ground, float *sMatrix, GLuint sScale, GLuint sTrans, GLuint sRot, GLuint texColor);
Ghost *makeGhost(char *baseFile, int numColors, int rows, int cols, GLuint tc, GLuint ts);
void drawGhost(Ghost *gho, float *sMatrix, GLuint sScale, GLuint sTrans, GLuint sRot, GLuint texColor);
void moveGhost(Ghost *gho, int xd, int yd, float xPow, float yPow);
void freeGhost(Ghost *g);
#endif
