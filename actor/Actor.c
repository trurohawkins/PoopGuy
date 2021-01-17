#include "aList.c"

Actor *makeActor(Form * f/*, Action *a*/) {
	Actor *newActor = (Actor*)calloc(1, sizeof(Actor));
	newActor->body = f;
	newActor->actionList = makeList();
	/*
	if (a != 0) {
		addToList(newActor->actionList, a);
	}
	*/
	return newActor;
}


void addAction(Actor *actor, Action *action) {
	addToList(actor->actionList, action);
}

void *removeAction(Actor *actor, Action *action) {
	return removeFromList(&(actor->actionList), action);
}

void deleteMyAction(Actor *actor, Action *action) {
	deleteAction(removeAction(actor, action));
}

void doActions(Actor *actor) {
	linkedList *a = actor->actionList;
	while (a != 0) {
		Action *act = (Action*) a->data;
		if (act->active == 1) {
			(*(act->fun))(actor->body, act);
		}
		a = a->next;
	}
}

void freeActionList(Actor *actor) {
	linkedList *a = actor->actionList;
	while (a != 0) {
		deleteAction((Action*)a->data);
		a = a->next;
	}
	freeList(&(actor->actionList));

}

void deleteActor(Actor *actor) {
	deleteForm(actor->body);
	freeActionList(actor);
	free(actor);
}
