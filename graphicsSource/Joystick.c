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
			int jid = *(int*)(head->data);
			printf("joystick# %i\n", jid);
		} else {
			printf("stick has null data\n");
		}
		head = head->next;
	}
}

void checkControllerInput() {
	linkedList *head = joystickList;
	GLFWgamepadstate state;
	while (head != 0) {
		if (head->data != 0) {
			int jid = *(int*)(head->data);
			if (glfwGetGamepadState(jid, &state)) {
				for (int i = 0; i < 15; i++) {
					if (state.buttons[i]) {
						char *s = "";
						if (state.buttons[i] == GLFW_PRESS) {
							s = "press";
						}
						printf("button[%i]:%s\n",i, s);
					}
					if (i < 6) {
						//printf("axes[%i]:%f\n", i, state.axes[i]);
					}
				}
			}
		}
		head = head->next;
	}
}
