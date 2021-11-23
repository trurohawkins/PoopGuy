#include "Input.h"
linkedList *curInput;
linkedList *controls;
#include "Joystick.c"


void initInput() {
	curInput = makeList();
	controls = makeList();
	Screen *screen = getWindow();
	glfwSetKeyCallback(screen->window, takeKeys);
	glfwSetMouseButtonCallback(screen->window, takeMouseButt);
	glfwSetScrollCallback(screen->window, takeScroll);
}

void addControl(char *inp, void (*n_func)(float)) {
	InpMap *im = (InpMap*)calloc(1, sizeof(InpMap));
	im->input = inp;
	im->func = n_func;
	addToList(&controls, im);
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

void processKeys() {
	linkedList *cur = curInput;
	if (cur != NULL && cur->data != NULL) {
		while (cur != NULL) {
			inpReceived *ir = (inpReceived*)cur->data;
			char *inp = ir->input;
			linkedList *con = controls;
			while (con != NULL) {
				InpMap *tmp = (InpMap*)con->data;
				char *c = tmp->input;
				if (strCompare(inp, c) == true) {
					tmp->func(ir->val);
					break;
				} 
				con = con->next;
			}
			cur = cur->next;
		}
		freeCurInput();
		curInput = makeList();
	}
}

void freeCurInput() {
	linkedList *tmp = curInput;
	while (tmp != NULL) {
		inpReceived *ir = (inpReceived*)tmp->data;
		free(ir->input);
		free(ir);
		linkedList *t = tmp;
		tmp = tmp->next;
		free(t);
	}
}	

void tmpFunc(float val) {
	printf("poopydoopy %f\n", val);
}

void freeInput() {
	freeList(&controls);
	freeList(&curInput);
}
