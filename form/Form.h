typedef struct Form {
	float color[3];
} Form;
Form *makeForm(float r, float g, float b);
void deleteForm(Form *f);

#include "../actor/Action.h"
#include "../actor/Actor.h"
#include "World.h"
#include "FormGraphics.h"
