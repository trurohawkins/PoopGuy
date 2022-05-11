#ifndef FORMGLFW
#define FORMGLFW
#include "../form/Form.h"
#include "../helper/helper.h"
#include "../graphics/glfwMain.h"
#include "Player.h"
#include "WorldView.h"
#include "god.h"
#include "DrawWorld.h"

int mainMenu();
char *getFileName();
void updateLoop();
void playGame();
void quitGame();
void saveGame();
void loadGame();
void newGame();
//void drawWorld2(World *w);
//void drawGrid(float *mat, int tMat, int sMat,  int rMat, int color, GLuint vLi);
//void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
//void setCenter(float cp[2]);
//void setFrame(int x, int y);
void setAnim(Form *f, Anim *a);
void setGrid(bool state);
void togglePauseMenu(void *,float val);
void toggleDebugDraw(void *,float val);
void toggleGod(void *,float);
void centerOnForm(Form *f);
void exitGame();
void saveMap();
void exitMenu();
#endif
