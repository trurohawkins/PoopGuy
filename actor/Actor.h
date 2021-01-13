#include "aList.h"

typedef struct Actor {
	Form *body;
	linkedList_t *actionList;
} Actor;

Actor *makeActor(Form * f, Action *a);
void addAction(Actor *actor, Action *action);
void doActions(Actor *actor);
void deleteActor(Actor *actor);
