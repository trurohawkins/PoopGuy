typedef struct Action {
	char active;
	void *vars;
	void (*fun)(Form*, struct Action* a);
} Action;



Action *makeAction(void (*fun)(Form*, Action*), void *);
void deleteAction(Action *action);
//void setActVar(Action *action, int index, int val);
void defaultAction();
#include "acts/actList.h"
