#ifndef INP
#define INP
#include "Joystick.h"
#include "glfwMain.h"

void initInput();
void takeKeys(GLFWwindow *window, int key, int scancode, int action, int mods);
void freeInput();

#endif
