typedef struct Action {
	int active;
	void (*fun)(void);
} Action;



Action *makeAction(void (*fun)(void));
void deleteAction(Action *action);
void defaultAction();
