#include "formglfw/FormGlfw.h"

bool doGL = true;

int main(int argc, char **argv) {
	bool showMenu = false;
	if (argc > 1) {
		if (argv[1][1] == 'g') {
			setGrid(true);
		} else if (argv[1][1] == 'm') {
			showMenu = true;
		}
	}
	srand(time(NULL));
	initDirections();
	int worldX = 100;
	int worldY = 100;
	int windowX = 200;
	int windowY = 200;
/*
	int arr[3] = {1, 2, 3};
	writeBinaryInt("poo.bin", arr, 3);
	writeBinaryInt("poo.bin", arr, 3);
	//fput32le(420, "poo.bin");
	printf("int size %li\n", sizeof(int));
	int *poo = readBinaryInt("poo.bin", 6);
	if (poo != 0) {
		for (int i = 0; i < 6; i++) {
			printf("saved and recieved %i\n", poo[i]);
		}
	}
	\*/
	initializeGLFW();
	setScreenMax(worldX);
	sizeScreen(windowX);
	initCamera(windowX, windowY);
	glfwSetJoystickCallback(joystickCallback);
	initJoyList();
	initText();
	initTexInts();
	initInput();
	makeTextureManager();
	initUILists();
	makePlayerManager();
	makeAnimList();
	initWorldDrawing();
	initTileSets();

	initRecipes(3, 10);
	addRecipe(makePoopPlayer, savePoopPlayer, 0);
	addRecipe(makeDirt, saveDirt, 1);
	addRecipe(makeStone, saveForm, 2);
	makeActorList();
	initPoopers();
	int menuVal = 1;
	if (showMenu) {
		menuVal = mainMenu();
		if (menuVal < 0) {
			freeUILists();
			deleteTextureManager();
			freePlayerManager();
			freeJoyList();
			freeInput();
			glfwTerminate();
			return 0;
		}
	}
	//if (!loadWorld("world.bin")) {
	if (menuVal != 2) {
		int Seedstring[4] = {1,2,3,4};
		makeWorld(worldX, worldY);
		printf("generating world\n");
		int **map = genMap(Seedstring);
		genRain(map);
		genWorld(map);
		//arrayToFile("mapSave.txt", map);
		freeMap(map);
		int xPos = (worldX * 0.8);
		int yPos = 1;
		for (int i = 0; i < getNumPoopers(); i++) {
			placeForm(xPos + (i*4),  yPos, makePoopPlayer(i));
			//poopers[i] = makePoopPlayer(xPos + (i*4), 1, i);
		}
		//printArray(map, worldX, worldY);
		//arrayToFile("mapSave.txt", map);
		//map = fileToArray("mapSave.txt");//
		//printArray(map, worldX, worldY);
	}
	setCamFunction(calculateFrameData);
	updateLoop();
	return 0;
}
