#ifndef INP
#define INP
#include "Joystick.h"
#include "glfwMain.h"

typedef struct InpMap
{
	char *input;
	float val;
	void (*func)(float);
} InpMap;

typedef struct inpReceived
{
	char *input;
	float val;
} inpReceived;

void initInput();
void addControl(char *inp, void(*n_func)(float));
void takeKeys(GLFWwindow *window, int key, int scancode, int action, int mods);
void takeMouseButt(GLFWwindow *window, int button, int action, int mods);
void takeScroll(GLFWwindow *window, double xoffset, double yoffset);
void processKeys();
void freeCurInput();
//InpMap *makeInputMap(char *str, void (*func)(void));
void tmpFunc(float);

void freeInput();

#endif
