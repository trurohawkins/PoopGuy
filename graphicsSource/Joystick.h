#ifndef JOY
#define JOY
#include <stdio.h>
#include <GL/glew.h>//loader of functions for backwards compatibility**
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "../helper/list.h"

void initJoyList();
void freeJoyList();
void addJoystick(int j);
void joystickCallback(int jid, int event);
void readJoysticks();
void checkControllerInput();
#endif
