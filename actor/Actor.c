#include "aList.c"

Actor *makeActor(Form * f, Action *a) {
	Actor *newActor = (Actor*)calloc(1, sizeof(Actor));
	newActor->body = f;
	newActor->actionList = (linkedList_t *)calloc(1, sizeof(linkedList_t));
	newActor->actionList->data = 0;
	newActor->actionList->next = 0;
	if (a != 0) {
		addToList(newActor->actionList, a);
	}
	//newActor->actionList->next = 0;
	return newActor;
}

void addAction(Actor *actor, Action *action) {
	addToList(actor->actionList, action);
}

void doActions(Actor *actor) {
	linkedList_t *a = actor->actionList;
	while (a != 0) {
		//void (*fun)(void) = a->data;
		//(*fun)();
		Action *act = (Action*) a->data;
		(*(act->fun))();
		a = a->next;
	}
}

void freeActionList(Actor *actor) {
	linkedList_t *a = actor->actionList;
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
