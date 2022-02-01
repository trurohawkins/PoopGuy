#ifndef GLFWgra
#define GLFWgra
#include "glad.h"
//#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
//#include<GL/gl.h>
#include <stdio.h>

#include "shaders/Shaders.h"
#include "input/Input.h"
#include "Anim.h"
#include "../helper/helper.h"

typedef struct Screen {
	GLFWwindow *window;
	int width;
	int height;
} Screen;

int initializeGLFW();
void glfwWindowSizeCallback(GLFWwindow *window, int width, int height);
GLuint squareVao2d();
GLuint lineVao2d();
GLuint makeVao2d(float *shape, int len);
GLuint makeSpriteVao(float sx, float sy);
Screen *getWindow();
GLuint getSP();
#endif
