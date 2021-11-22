//#include "form/Form.h"
//#include "graphicsSource/Graphics.h"
#include "FormGraphics.c"

bool doGL = true;
Player *poopGuy;

int main(int argc, char **argv) {
	if (argc > 1) {
		if (argv[1][1] == 'n') {
			doGL = false;
		} else if (argv[1][1] == 'g') {
			setGrid(true);
		}
	}

	srand(time(NULL));
	initDirections();
	int worldX = 1000;
	int worldY = 500;
	int windowX = 500;
	int windowY = 500;
	makeWorld(worldX, worldY);
	dirtFloor(100);
	makeCircle(30, 50, 5);
	atexit(exitGame);
	poopGuy = makePlayer(2, 2);
	placeForm(44, 30, poopGuy->me->body);
	setCenter(poopGuy->me->body->pos);
	checkSide(poopGuy->me->body, 1, 0, true);
	/*Actor *rock = makeActor(makeForm(0.3, 0.3, 0.3));
	Action *move =  makeMove();
	addAction(rock, move);
	addAction(rock, makeGravity(move->vars));
	placeForm(13, 40, rock->body);
*/
	makeActorList();
	addActor(poopGuy->me);
	//addActor(rock);
//	stomachStuff(poopGuy->me->body, poopGuy->eatPoop);
//	eatPooVar *ep = (eatPooVar*)(poopGuy->eatPoop->vars);
//	ep->pooping = 1;
	if (doGL) {
		initializeGLUT(argc, argv, windowX, windowY);
		glutFunctions(drawWorld, update, keyDown, keyUp);
	}	
	return 0;
}
