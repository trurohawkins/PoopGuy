typedef struct linkedList
{
	void *data;
	struct linkedList *next;
} linkedList_t;

#include <stdio.h>
#include <stdlib.h>

void addToList(linkedList_t *head, void *item);

void freeList(linkedList_t **ll);
