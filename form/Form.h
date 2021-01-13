typedef struct Form
{
	float color[3];
} Form;

Form *makeForm(float r, float g, float b);
void deleteForm(Form * form);

#include "FormGraphics.h"
#include "World.h"
