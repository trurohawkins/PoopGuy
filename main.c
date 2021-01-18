#include "form/Form.h"

Actor *nicCage;
Action *nicMove;
void update(int value);
void keyDown(unsigned char, int, int);
void keyUp(unsigned char, int, int);
void exitGame();

int main(int argc, char **argv) {
	srand(time(NULL));
	initDirections();
	int worldX = 50;
	int worldY = 20;
	int windowX = 500;
	int windowY = 500;
	makeWorld(worldX, worldY);
	dirtFloor(3);
	atexit(exitGame);
	
	Form *f = makeForm(1, 1, 1);
//	moveVar* mv = (moveVar *)calloc(1, sizeof(moveVar));
	nicMove = makeMove();// makeAction(&move, mv);
//	nicMove->active = 1;
	//setActVar(nicMove, 1, 20);
	//setActVar(nicMove, 2, 3);
	nicCage = makeActor(f);
	placeForm(3, 7, nicCage->body);
	addAction(nicCage, nicMove);
	//setMoveSpeed(nicMove->vars, 1);
	/*
	printf("start pos: %i, %i\n", nicCage->body->pos[0], nicCage->body->pos[1]);
	addForce(nicMove->vars, 0, 1, 0, 10);
	addForce(nicMove->vars, 1, 0, 10, 0);
	doActions(nicCage);
	printf("end pos: %i, %i\n", nicCage->body->pos[0], nicCage->body->pos[1]);
	*/
	/*
	moveVar *grav = (moveVar *)(calloc)(1, sizeof(moveVar));
	setMoveSpeed(grav, 4);
	setMoveDirY(grav, -1);
	Action *nicGrav = makeAction(&move, grav);
	nicGrav->active = 1;
	addAction(nicCage, nicGrav);
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
		addForce(nicMove->vars, 0, 1, 0, 1);
	}
	if (key == 97) { //a
		addForce(nicMove->vars, -1, 0, 1, 0);
	}
	if (key == 115) {//s
		addForce(nicMove->vars, 0, -1, 0, 1);
	}
	if (key == 100) {//d
		addForce(nicMove->vars, 1, 0, 1, 0);
	}
}

void keyUp(unsigned char key, int mx, int my) {
	if (key == 119) {
		addForce(nicMove->vars, 0, -1, 0, 1);
	}
	if (key == 97) { //a
		addForce(nicMove->vars, 1, 0, 1, 0);
	}
	if (key == 115) {
		addForce(nicMove->vars, 0, 1, 0, 1);
	}
	if (key == 100) {//d
		addForce(nicMove->vars, -1, 0, 1, 0);
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
}
