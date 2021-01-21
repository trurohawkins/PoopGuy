#include "form/Form.h"

Player *poopGuy;
void update(int value);
void keyDown(unsigned char, int, int);
void keyUp(unsigned char, int, int);
void exitGame();

int main(int argc, char **argv) {
	srand(time(NULL));
	initDirections();
	int worldX = 50;
	int worldY = 50;
	int windowX = 500;
	int windowY = 500;
	makeWorld(worldX, worldY);
	dirtFloor(3);
	atexit(exitGame);
	poopGuy = makePlayer();
	placeForm(0, 0, poopGuy->me->body);
	setCenter(poopGuy->me->body->pos);

	Actor *rock = makeActor(makeForm(0.3, 0.3, 0.3));
	Action *move =  makeMove();
	addAction(rock, move);
	addAction(rock, makeGravity(move->vars));
	placeForm(3, 40, rock->body);

	makeActorList();
	addActor(poopGuy->me);
	addActor(rock);
	
//	stomachStuff(poopGuy->me->body, poopGuy->eatPoop);
//	eatPooVar *ep = (eatPooVar*)(poopGuy->eatPoop->vars);
//	ep->pooping = 1;

	initializeGLUT(argc, argv, windowX, windowY);
	glutIgnoreKeyRepeat(1);	
	glutDisplayFunc(drawWorld);	
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(25, update, 0);
	glutMainLoop();	
	
	return 0;
}

void keyDown(unsigned char key, int mx, int my) {
	if (key == 27) {
		glutLeaveMainLoop();
	}
	keyPressPlayer(poopGuy, key);
}

void keyUp(unsigned char key, int mx, int my) {
	keyReleasePlayer(poopGuy, key);
}

void update(int value) {
	actorListDo();
	setCenter(poopGuy->me->body->pos);
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}
void exitGame() {
	printf("coochy");
	deleteWorld();
	deletePlayer(poopGuy);
	deleteActorList();
	freeDirections();
}
