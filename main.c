#include "form/Form.h"

int FPS = 60;
bool paused = false;
bool doGL = true;
Player *poopGuy;
void update(int value);
void keyDown(unsigned char, int, int);
void keyUp(unsigned char, int, int);
void joystick(unsigned int buttonmask, int x, int y, int z);
void exitGame();

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
	dirtFloor(10);
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
		glutIgnoreKeyRepeat(1);	
		glutDisplayFunc(drawWorld);	
		glutKeyboardFunc(keyDown);
		glutKeyboardUpFunc(keyUp);
		glutJoystickFunc(joystick, 25);
		glutTimerFunc(1000/FPS, update, 0);
		glutMainLoop();
	}	
	return 0;
}

void joystick(unsigned int buttonmask, int x, int y, int z) {
	printf("getting joystick %i, %i, %i axis values\n", x, y, z);
	printf("buttonmask %u\n", buttonmask);
}

void keyDown(unsigned char key, int mx, int my) {
	if (key == 27) {
		glutLeaveMainLoop();
	} else if (key == 96) {
		paused = !paused;
	}
	keyPressPlayer(poopGuy, key);
}

void keyUp(unsigned char key, int mx, int my) {
	keyReleasePlayer(poopGuy, key);
}

void update(int value) {
	if (!paused) {
		actorListDo();
	}
	setCenter(poopGuy->me->body->pos);
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, update, 0);
}
void exitGame() {
	deleteWorld();
	deletePlayer(poopGuy);
	deleteActorList();
	freeDirections();
}
