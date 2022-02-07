#ifndef LL
#define LL
typedef struct linkedList
{
	void *data;
	struct linkedList *next;
	struct LinkedList *prev;
} linkedList;

#include <stdio.h>
#include <stdlib.h>

linkedList *makeList();

void addToList(linkedList **head, void *item);
bool checkList(linkedList **head, void *item, bool (*cmp)(void*, void*));
void *removeFromList(linkedList **head, void *item);
void *removeFromListInt(linkedList **head, int item);
void freeList(linkedList **ll);
void deleteList(linkedList **ll, void (*deleteFunc)(void*));
void freeListSaveObj(linkedList **ll);
#endif
