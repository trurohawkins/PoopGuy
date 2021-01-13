Action *makeAction(void (*fun)(void)) {
	Action *newAction = (Action*)calloc(1, sizeof(Action));
	newAction->active = 1;
	if (fun == 0) {
		newAction->fun = &defaultAction;
	} else {
		newAction->fun = fun;
	}
	return newAction;
}

void deleteAction(Action *action) {
	free(action);
}

void defaultAction() {
	printf("I am acting\n");
}
