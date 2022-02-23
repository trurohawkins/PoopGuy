#include "formglfw/FormGlfw.h"

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
	int worldY = 100;
	int windowX = 60;
	int windowY = 20;
	makeWorld(worldX, worldY);
	initCamera(windowX, windowY);
	int Seedstring[4] = {1,2,3,4};
	int** map = genMap(Seedstring);
	genRain(map);
	genWorld(map);
	freeMap(map);
	//printArray(map, worldX, worldY);
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
