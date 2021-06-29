#include "form/Form.h"
#include "graphicsSource/glfwMain.h"

void updateLoop();
void drawWorld(World *w, float *mat, int tMat, int sMat, int rMat, int color, GLuint squa);
void drawGrid(float *mat, int tMat, int sMat,  int rMat, int color, GLuint vLi);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void setCenter(float cp[2]);
void setGrid(bool state);
void exitGame();
