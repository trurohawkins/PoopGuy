typedef struct formStack {
	Form *type;
	int count;
} formStack;

typedef struct eatPooVar {
	linkedList *stomach;
	int dir;
	bool pooping;
	bool eating;
	int bite[2];
	int xBite;
	int yBite;
} eatPooVar;

Action *makeStomach(int bite);

void changeDir(eatPooVar *ep, int dir);
void stomachStuff(Form *f, Action *a);
void addToStack(Form *f, Action *a);
Form *removeFromStack();
