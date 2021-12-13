#include "Input.h"
#include "Joystick.c"
linkedList *curInput;


void initInput() {
	curInput = makeList();
	Screen *screen = getWindow();
	glfwSetKeyCallback(screen->window, takeKeys);
	glfwSetMouseButtonCallback(screen->window, takeMouseButt);
	glfwSetScrollCallback(screen->window, takeScroll);
}

linkedList *getCurInput() {
	return curInput;
}

void takeKeys(GLFWwindow *window, int key, int scancode, int action, int mods) {
	inpReceived *ir = (inpReceived*)malloc(sizeof(inpReceived));
	char *keyString = (char *)malloc(4 * sizeof(char));
	keyString[0] = 'K';
	keyString[1] = 48;//add player info later
	keyString[2] = key;
	keyString[3] = '\0';
	ir->input = keyString;
	ir->val = action;
	addToList(&curInput, ir);
}

void takeMouseButt(GLFWwindow *window, int button, int action, int mods) {
	inpReceived *ir = (inpReceived*)malloc(sizeof(inpReceived));
	char *mouseString = (char *)malloc(4 *sizeof(char));
	mouseString[0] = 'M';
	mouseString[1] = 48;
	mouseString[2] = button + 48;
	mouseString[3] = '\0';
	ir->input = mouseString;
	ir->val = action;
	addToList(&curInput, ir);
	
}

void takeScroll(GLFWwindow *window, double xoffset, double yoffset) {
	printf("mouse scroll %d, %d\n", xoffset, yoffset);
}

void clearInput() {
		freeCurInput();
		curInput = makeList();
}

void freeCurInput() {
	linkedList *tmp = curInput;
	while (tmp != NULL) {
		inpReceived *ir = (inpReceived*)tmp->data;
		if (ir != NULL) {
			free(ir->input);
		}
		free(ir);
		linkedList *t = tmp;
		tmp = tmp->next;
		free(t);
	}
}	

void tmpFunc(void *, float val) {
	printf("poopydoopy %f\n", val);
}

void freeInput() {
//	freeList(&players);
	freeList(&curInput);
}
