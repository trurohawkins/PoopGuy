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
	int worldY = 300;
	int windowX = 60;
	int windowY = 60;
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
		initText();
		updateLoop();
		/*
		Screen *screen = getWindow();
		while(!glfwWindowShouldClose(screen->window)) {
			if(glfwGetKey(screen->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(screen->window, 1);
			}
				glClearColor(0.1, 0.2, 0.4, 1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				renderText("POOPGUY", 25, 25, 1);		
				//renderText("ORDIT", screen->width/2, screen->height/2, 1);
				glfwSwapBuffers(screen->window);
			glfwPollEvents();

		}
		*/
		//initializeGLUT(argc, argv, windowX, windowY);
		//glutFunctions(drawWorld, update, keyDown, keyUp);
	}	
	return 0;
}
