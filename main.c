#include "form/Form.h"

Actor *nicCage;
Action *nicMove;
void update(int value);
void keyDown(unsigned char, int, int);
void keyUp(unsigned char, int, int);
void exitGame();

int main(int argc, char **argv) {
	initDirections();
	int worldX = 50;
	int worldY = 50;
	int windowX = 500;
	int windowY = 500;
	makeWorld(worldX, worldY);
	atexit(exitGame);
	
	Form *f = makeForm(1, 1, 1);
	moveVar* mv = (moveVar *)calloc(1, sizeof(moveVar));
	nicMove = makeAction(&move, mv);
	nicMove->active = 0;
	//setActVar(nicMove, 1, 20);
	//setActVar(nicMove, 2, 3);
	nicCage = makeActor(f);
	placeForm(0, 9, nicCage->body);
	addAction(nicCage, nicMove);
	setMoveSpeed(nicMove->vars, 1);
	moveVar *grav = (moveVar *)(calloc)(1, sizeof(moveVar));
	setMoveSpeed(grav, 4);
	setMoveDir(grav, 2);
	Action *nicGrav = makeAction(&move, grav);
	nicGrav->active = 1;
	addAction(nicCage, nicGrav);
	/*
	deleteWorld();
	deleteActor(nicCage);
	*/	
	initializeGLUT(argc, argv, windowX, windowY, worldX, worldY);
	
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
		setMoveDir(nicMove->vars, 0);
		nicMove->active = 1;
					
	}
	if (key == 97) { //a
		setMoveDir(nicMove->vars, 1);
		nicMove->active = 1;
	}
	if (key == 115) {//s
		setMoveDir(nicMove->vars, 2);
		nicMove->active = 1;
	}
	if (key == 100) {//d
		setMoveDir(nicMove->vars, 3);
		nicMove->active = 1;
	}
}

void keyUp(unsigned char key, int mx, int my) {
	if (key == 119 || key == 97 || key == 115 || key == 100) {//w
		nicMove->active = 0;
	}
}

void update(int value) {
	//(*(nicCage->act->fun))(0);
	doActions(nicCage);
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

void exitGame() {
	printf("coochy");
	deleteWorld();
	deleteActor(nicCage);
}
