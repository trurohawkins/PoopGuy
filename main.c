#include "form/Form.h"

Actor *nicCage;
Action *nicMove;
Action *nicJump;
int nicSpeed = 10;
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
	
	Form *f = makeForm(1, 1, 1);
//	moveVar* mv = (moveVar *)calloc(1, sizeof(moveVar));
	nicMove = makeMove();// makeAction(&move, mv);
	Action *grav = makeGravity(nicMove->vars);
	nicJump = makeJump(nicMove->vars, grav);
//	nicMove->active = 1;
	//setActVar(nicMove, 1, 20);
	//setActVar(nicMove, 2, 3);
	nicCage = makeActor(f);
	placeForm(3, 40, nicCage->body);
	addAction(nicCage, nicMove);
	addAction(nicCage, grav);
	addAction(nicCage, nicJump);
	/*
	addForce(nicMove->vars, 0, 1, 0, 10);
	addForce(nicMove->vars, 1, 0, 10, 0);
	doActions(nicCage);
	*/
	
	setCenter(nicCage->body->pos);
	initializeGLUT(argc, argv, windowX, windowY);
	glutIgnoreKeyRepeat(1);	
	glutDisplayFunc(drawWorld);	
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(25, update, 0);
	glutMainLoop();	
	return 0;
}

unsigned char keyPressed;
unsigned char keyReleased;
void keyDown(unsigned char key, int mx, int my) {
	if (key == 27) {
		glutLeaveMainLoop();
	}
	if (key == 119 || key == 97 || key == 115 || key == 100) {//w
		keyPressed = key;
	}
	
	if (key == 119) {
		addForce(nicMove->vars, 0, nicSpeed);
	}
	if (key == 97) { //a
		addForce(nicMove->vars, -nicSpeed, 0);
	}
	if (key == 115) {//s
		addForce(nicMove->vars, 0, -nicSpeed);
	}
	if (key == 100) {//d
		addForce(nicMove->vars, nicSpeed, 0);
	}
	if (key == 32) {
		startJump(nicJump);
		//nicJump->active = 1;	
	}
}

void keyUp(unsigned char key, int mx, int my) {
	if (key == 119) {
		addForce(nicMove->vars, 0, -nicSpeed);
	}
	if (key == 97) { //a
		addForce(nicMove->vars, nicSpeed, 0);
	}
	if (key == 115) {
		addForce(nicMove->vars, 0, nicSpeed);
	}
	if (key == 100) {//d
		addForce(nicMove->vars, -nicSpeed, 0);
	}
	 //	|| key == 97 || key == 115 || key == 100) {//w
}

void update(int value) {
	doActions(nicCage);
	setCenter(nicCage->body->pos);
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

void exitGame() {
	printf("coochy");
	deleteWorld();
	deleteActor(nicCage);
	freeDirections();
}
