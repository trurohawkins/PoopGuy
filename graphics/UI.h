#ifndef USERINTERFACE
#define USERINTERFACE

typedef struct UI {
	float xp;
	float yp;
	float xSize;
	float ySize;
	bool xInvert;
	bool yInvert;
	int roto;
	Anim *a;
} UI;

void initBackgroundUI();
void addBackground(UI *ui); 
void drawBG(float *sMatrix);
void freeBG();
void initForegroundUI();
void addForeground(UI *ui); 
void drawFG(float *sMatrix);
void freeFG();
void drawGround(linkedList *ground, float *sMatrix);
UI *makeUI(char *baseFile, int numColors, int rows, int cols);
void drawUI(UI *ui, float *sMatrix);
void moveUI(UI *ui, int xd, int yd, float xPow, float yPow);
void freeUI(UI *ui);
#endif
