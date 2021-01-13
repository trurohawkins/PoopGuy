#include <stdio.h>
#include <stdlib.h>
#include "Action.h"
#include "Action.c"
#include "Actor.h"
#include "Actor.c"

void poo() {
	printf("pooping\n");
}

void eat() {
	printf("eating\n");
}

int main() {
	/*
	linkedList_t *list = (linkedList_t*)calloc(1, sizeof(linkedList_t));
	int num = 10;
	addToList(list, &num);
	int n2 = 34;
	int n4 = 100;
	addToList(list, &n2);
	addToList(list, &n4);

	printList(list);
	freeList(&list);
	*/
	Action *p = makeAction(&poo);
	Action *e = makeAction(&eat);
	Actor *a = makeActor(p);
	addAction(a, e);
	doActions(a);
	//freeList(&(a->actionList));
	//deleteAction(p);
	//deleteAction(e);
	deleteActor(a);

	return 0;
}	
