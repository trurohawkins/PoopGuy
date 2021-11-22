#include "Input.h"
#include "Joystick.c"

linkedList *curInput;

void initInput() {
	curInput = makeList();
	Screen *screen = getWindow();
	glfwSetKeyCallback(screen->window, takeKeys);
	printf("iitalized Input\n");
}

void takeKeys(GLFWwindow *window, int key, int scancode, int action, int mods) {
	printf("key ppressed %i and actuin: %i\n", key, action);
}

void freeInput() {
	freeList(&curInput);
}
