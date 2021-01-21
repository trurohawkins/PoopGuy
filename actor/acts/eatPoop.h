typedef struct formStack {
	Form *type;
	int count;
} formStack;

typedef struct eatPooVar {
	linkedList *stomach;
	int dir;
	int pooping;
} eatPooVar;

Action *makeStomach();

void stomachStuff(Form *f, Action *a);
void addToStack(Form *f, Action *a);
Form *removeFromStack();
