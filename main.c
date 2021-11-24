#include "formglfw/FormGlfw.c"
#include "formglfw/Player.c"

bool doGL = true;

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
	int worldX = 300;
	int worldY = 300;
	int windowX = 100;
	int windowY = 100;
	makeWorld(worldX, worldY);
	setFrame(windowX, windowY);
	int Seedstring[4] = {1,2,3,4};
	int** map = genMap(Seedstring);
	int** Rmap = genRain(map);
	printArray(map, worldX, worldY);
	genWorld(map);
	freeMap(map);
	atexit(exitGame);
	pooper = makePoopGuy(3, 3);
	placeForm(1, worldY - 3, pooper->me->body);
	checkSide(pooper->me->body, 1, 0, true);
	/*Actor *rock = makeActor(makeForm(0.3, 0.3, 0.3));
	Action *move =  makeMove();
	addAction(rock, move);
	addAction(rock, makeGravity(move->vars));
	placeForm(13, 40, rock->body);
*/
	makeActorList();
	addActor(pooper->me);
	//addActor(rock);
//	stomachStuff(pooper->me->body, pooper->eatPoop);
//	eatPooVar *ep = (eatPooVar*)(pooper->eatPoop->vars);
//	ep->pooping = 1;
	if (doGL) {
		initializeGLFW();
		glfwSetJoystickCallback(joystickCallback);
		initJoyList();
		updateLoop();
		//initializeGLUT(argc, argv, windowX, windowY);
		//glutFunctions(drawWorld, update, keyDown, keyUp);
	}	
	return 0;
}
