#ifndef FORMGLFW
#define FORMGLFW
#include "../form/Form.h"
#include "../graphics/glfwMain.h"
//#include "helper/file.h"

void updateLoop();
void drawWorld(World *w, int tMat, int sMat, int rMat, int color, GLuint squa, int sTrans, int sScale);
void drawFormSprite(Form *f, float *sMatrix, float xSize, float ySize, int xp, int yp, GLuint sScale, GLuint sTrans);
void drawGrid(float *mat, int tMat, int sMat,  int rMat, int color, GLuint vLi);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void setCenter(float cp[2]);
void setGrid(bool state);
void toggleGod(float);
void exitGame();
void setFormRoto(Form *f, int dir);
#endif
