#include "Joystick.h"

linkedList *joystickList = 0;

void initJoyList() {
	for (int i = 0; i < 16; i++) {
		if (glfwJoystickPresent(i)) {
			printf("joy stick connected %i\n", i);
			addJoystick(i);
		}
	}
	readJoysticks();
}

void freeJoyList() {
	freeList(&joystickList);
}

void addJoystick(int j) {
	int *js = (int*)calloc(1,sizeof(int));
	*js = j;
	if (joystickList == 0) {
		joystickList = makeList();
		joystickList->data = js;
	} else {
		addToList(&joystickList, js);
	}
}

void joystickCallback(int jid, int event) {
	if (event == GLFW_CONNECTED) {
		addJoystick(jid);
	} else if (event == GLFW_DISCONNECTED) {
		free(removeFromListInt(&joystickList, jid));
	}
	readJoysticks();
}

void readJoysticks() {
	printf("reading sticks\n");
	linkedList *head = joystickList;
	while (head != 0) {
		if (head->data != 0) {
			printf("joystick# %i\n", *(int*)(head->data));
		} else {
			printf("stick has null data\n");
		}
		head = head->next;
	}
}
