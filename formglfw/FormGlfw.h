#ifndef FORMGLFW
#define FORMGLFW
#include "../form/Form.h"
#include "../helper/helper.h"
#include "../graphics/glfwMain.h"
#include "Player.h"

typedef struct AnimOrder {
	int order;
	linkedList *anims;
	linkedList *poses;
} AnimOrder;
//#include "helper/file.h"

void updateLoop();
void drawWorld(World *w, int tMat, int sMat, int rMat, int color, GLuint squa, int sTrans, int sScale, int sRot);
void drawFormSprite(Form *f, float *sMatrix, float xSize, float ySize, float xp, float yp, GLuint sScale, GLuint sTrans, GLuint sRot);
void drawGrid(float *mat, int tMat, int sMat,  int rMat, int color, GLuint vLi);
//void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
AnimOrder *makeAnimOrder(int order);
void addFormToAnim(AnimOrder *ao, Form *f, float x, float y);
void drawAnimOrder(AnimOrder *ao, float *sMatrix, float xSize, float ySize,  GLuint sScale, GLuint sTrans, GLuint sRot);
void freeAnimOrder(AnimOrder *ao);
void setCenter(float cp[2]);
void setAnim(Form *f, Anim *a);
void setGrid(bool state);
void togglePause(void *,float val);
void toggleGod(void *,float);
void exitGame();
#endif
