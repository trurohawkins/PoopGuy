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

Joypad *makeJoypad(int j) {
	Joypad *jp = (Joypad *)calloc(1, sizeof(Joypad));
	jp->jid = j;
	jp->buttState = (bool *)calloc(15, sizeof(bool));
	jp->axeState = (float *)calloc(6, sizeof(float));
	//jp->defAxeState - (float *)calloc(6, sizeof(float));
	return jp;
}

void freeJoyList() {
	linkedList *cur = joystickList;	
	linkedList *tmp = NULL;
	while (cur != NULL) {
		freeJoypad((Joypad*)cur->data);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void addJoystick(int j) {
	Joypad *jp = makeJoypad(j);
	if (joystickList == 0) {
		joystickList = makeList();
		joystickList->data = jp;
	} else {
		addToList(&joystickList, jp);
	}
}

void joystickCallback(int jid, int event) {
	if (event == GLFW_CONNECTED) {
		addJoystick(jid);
	} else if (event == GLFW_DISCONNECTED) {
		//free(removeFromList(&joystickList, jid));
		removeJoypad(&joystickList, jid);
	}
	readJoysticks();
}

void readJoysticks() {
	printf("reading sticks\n");
	linkedList *head = joystickList;
	while (head != 0) {
		if (head->data != 0) {
			//int jid = *(int*)(head->data);
			Joypad *jp = (Joypad*)(head->data);
			int jid = jp->jid;
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
			Joypad *jp = (Joypad *)head->data;
			int jid = jp->jid;
			if (glfwGetGamepadState(jid, &state)) {
				for (int i = 0; i < 15; i++) {
					if (state.buttons[i]) {
						if (state.buttons[i] == GLFW_PRESS && jp->buttState[i] == false) {
							joyButtString(jid, i, 1);
							jp->buttState[i] = true;
						} 
					} else if (jp->buttState[i] == true) {
							joyButtString(jid, i, 0);
							jp->buttState[i] = 0;

					}
					if (i < 6) {
						if ((i < 4 && fabs(state.axes[i]) > 0.0001) || (i >=4 && state.axes[i] > -1)) {
							if (state.axes[i] != jp->axeState[i]) {
								//printf("axes[%i]:%f\n", i, state.axes[i]);
								joyAxeString(jid, i, state.axes[i]);
								jp->axeState[i] = state.axes[i];
							}
						} else if (state.axes[i] != jp->axeState[i]) {
							joyAxeString(jid, i, 0);
							jp->axeState[i] = state.axes[i];
						}
					} 
				}
			}
		}
		head = head->next;
	}

}

char *joyButtString(int jid, int butt, int onoff) {
	inpReceived *ir = (inpReceived*)malloc(1 * sizeof(inpReceived));
	char *buttString = (char *)malloc(4 * sizeof(char));
	buttString[0] = 'J';
	buttString[1] = jid + 48;
	buttString[2] = butt + 48;
	//buttString[3] = onoff + 48;
	buttString[3] = '\0';
	ir->input = buttString;
	ir->val = onoff;
	//printf("button:%s\n", buttString);
	addToList(&curInput, ir);
	return buttString;
}

void joyAxeString(int jid, int axes, float val) {
	inpReceived *ir = (inpReceived*)malloc(1 * sizeof(inpReceived));
	char *axeString = (char *)malloc(4 * sizeof(char));
	axeString[0] = 'A';
	axeString[1] = jid + 48;
	axeString[2] = axes + 48;
	//axeString[3] = onoff + 48;
	axeString[3] = '\0';
	ir->input = axeString;
	if (axes % 2 == 1 && axes < 4) {//invert y axis but not for triggers
		val *= -1;
	}
	ir->val = val;
	//printf("button:%s val:%f\n", axeString, val);
	addToList(&curInput, ir);
}

Joypad *getJoypad(int jid) {
	linkedList *cur = joystickList;
	while (cur != 0) {
		Joypad *jp = (Joypad*)cur->data;
		if (jp->jid == jid) {
			return jp;
		}
	}
	return NULL;
}

void removeJoypad(linkedList **cur, int jid) {
	void *data = NULL;
	Joypad *j = (Joypad*)(*cur)->data;
	if (j->jid == jid) {
		linkedList *oh = *cur;
		(*cur) = (*cur)->next;
		data = oh->data;
		free(oh);
	} else {
		linkedList *tmp = (*cur)->next;
		linkedList *pre = *cur;
		while (tmp != NULL) {
			j = (Joypad*)(*cur)->data;
			if (j->jid == jid) {
				pre->next = tmp->next;
				data = tmp->data;
				free(tmp);
				tmp = pre->next;
			} else {
				tmp = tmp->next;
			}
		}
		pre = pre->next;
	}
	freeJoypad((Joypad*)data);
}

void freeJoypad(Joypad *jp) {
	free(jp->buttState);
	free(jp->axeState);
	free(jp);
}
