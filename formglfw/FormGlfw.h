#ifndef FORMGLFW
#define FORMGLFW
#include "../form/Form.h"
#include "../helper/helper.h"
#include "../graphics/glfwMain.h"
#include "Player.h"
#include "Camera.h"
#include "DrawWorld.h"

void updateLoop();
//void drawWorld2(World *w);
void drawWorldOld(World *w, int tMat, int sMat, int rMat, int color, GLuint squa);
void drawGrid(float *mat, int tMat, int sMat,  int rMat, int color, GLuint vLi);
//void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
//void setCenter(float cp[2]);
//void setFrame(int x, int y);
void setAnim(Form *f, Anim *a);
void setGrid(bool state);
void togglePause(void *,float val);
void toggleDebugDraw(void *,float val);
void toggleGod(void *,float);
void exitGame();
#endif
