#include "FormGlfw.h"
#include "Player.c"
#include "../controllerDB.c"

float centerX;
float centerY;
int frameX = 50;
int frameY = 50;
PoopGuy *pooper;
int numPlayers = 2;
bool gridOn = false;
bool paused = false;
bool godMode = false;
float *godPos;
int texColor;

void updateLoop() {
	//GLFWwindow *window
	Screen *screen = getWindow();
	//glfwSetKeyCallback(screen->window, keyCallback);
	initInput();
	GLuint squa = squareVao2d();
	GLuint vLi = lineVao2d(0);
	//GLuint hLi = lineVao2d(1);
	GLuint baseShader = getSP(0);//makeShaderProgram("graphicsSource/matVS.glsl", "graphicsSource/simpFS.glsl");
	GLuint texShader = getSP(1);
	if (baseShader != 0) {
		int tMat = glGetUniformLocation(baseShader, "tMat");
		if (tMat == -1) {
			printf("vert doesnt have a var tMat\n");
		}
		int sMat = glGetUniformLocation(baseShader, "sMat");
		if (sMat == -1) {
			printf("vert doesnt have a var sMat\n");
		}
		int rMat = glGetUniformLocation(baseShader, "rMat");
		if (rMat == -1) {
			printf("vert doesnt have a var rMat\n");
		}
		int drawColor = glGetUniformLocation(baseShader, "inputColor");
		if (drawColor == -1) {
			printf("frag doesnt have a var drawColor\n");
		}
		/*
		int texC = glGetUniformLocation(texShader, "texCoordShift");
		if (texC == -1) {
			printf(":38 couldnt get text coordinates from shader\n");
		}
		*/
		int spriteTrans = glGetUniformLocation(texShader, "tMat");
		if (spriteTrans == -1) {
			printf("vert doesnt have a var tMat\n");
		}
		int spriteScale = glGetUniformLocation(texShader, "sMat");
		if (spriteScale == -1) {
			printf("vert doesnt have a var sMat\n");
		}
		int spriteRot = glGetUniformLocation(texShader, "rMat");
		int tcScale = glGetUniformLocation(texShader, "tcScale");
		int tcTrans = glGetUniformLocation(texShader, "tcTrans");
		texColor = glGetUniformLocation(texShader, "colorShift");
		if (texColor == -1) {
			printf("frag doesnt have a var colorShift\n");
		}
		glUniform3f(texColor, 255, 255, 255);
		float tscMat [] = {
			//1.0f/6, 0.0, 0.0,
			//0.0, 1.0f/4, 0.0,
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		};
		float ttcMat [] = {
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,//-1.0f/4,
			0.0, 0.0, 1.0,
		};
		/*
		float tscMat [] = {
			1.0, 0.0,
			0.0, 1.0f
		};
		*/
		float matrix[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
		glUseProgram(baseShader);
		glUniformMatrix4fv(rMat, 1, GL_TRUE, matrix);
		glUseProgram(texShader);
		glUniformMatrix3fv(tcScale, 1, GL_TRUE, tscMat);
		glUniformMatrix3fv(tcTrans, 1, GL_TRUE, ttcMat);
		glUniformMatrix4fv(spriteTrans, 1, GL_TRUE, matrix);
		glUniformMatrix4fv(spriteScale, 1, GL_TRUE, matrix);
		World *w = getWorld();
		makePlayerManager();
		makeActorList();
		makeAnimList();
		makeTextureManager();
		initBackgroundGhosts();
		initForegroundGhosts();
		for (int i = 0; i < numPlayers; i++) {
			PoopGuy* tmp = makePoopPlayer(1 + (i*4), 2, i, tcTrans, tcScale);
			if (i == 0) {
				pooper = tmp;
			}
		}
		//cloud = makeGhost("resources/cloud.png", 1, 1, 1, tcTrans, tcScale);
		Ghost *cloud2 = makeGhost("resources/demonghost.png", 0, 1, 1, tcTrans, tcScale);
		//addBackground(cloud);
		addForeground(cloud2);
		/*
		Form *f = makeForm(1,1,1,1,1);
		placeForm(10, 10, f);
		Anim *h = makeAnim("resources/Heart.png", 1, 1, tcTrans, tcScale);
		setScale(h, 10, 10);
		GLuint sv = makeSpriteVao(1,1);
		animAddVao(h, sv);
		setAnim(f, h);
		*/
		//char *mappings = fileToString("gamecontrollerdb.txt");
		//const char *cMap = (const char*)mappings;
		glfwUpdateGamepadMappings(gamecontrollerdb);
		//free(mappings);
		Player *nullPlayer = makePlayer(NULL, -1, NULL);
		addControl(nullPlayer, "K0G", toggleGod);
		addControl(nullPlayer, "K0P", togglePause);
		godPos =  (float*)calloc(2, sizeof(float));
		godPos[0] = getWorld()->x /2;
		godPos[1] = getWorld()->y /2;

		while(!glfwWindowShouldClose(screen->window)) {
			glfwPollEvents();
			checkControllerInput();
			processKeys();
			if(glfwGetKey(screen->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(screen->window, 1);
			}
			if (!paused) {
				AnimListAnimate();
				actorListDo();
				groundWater();
				if (!godMode && pooper != NULL) {
					setCenter(pooper->me->body->pos);
				} else {
					setCenter(godPos);
				}
			}
			glClearColor(0.1, 0.2, 0.4, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			if (gridOn) {
				drawGrid(matrix, tMat, sMat, rMat, drawColor, vLi);
			}
			drawWorld(w, tMat, sMat, rMat, drawColor, squa, spriteTrans, spriteScale, spriteRot);
			glfwSwapBuffers(screen->window);
		}
		exitGame();
	}
}

void drawWorld(World *w, int tMat, int sMat, int rMat, int color, GLuint squa, int sTrans, int sScale, int sRot) {
		float mat[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
		float sMatrix[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
	glUniformMatrix4fv(rMat, 1, GL_TRUE, mat);
	GLuint baseShader = getSP(0);//makeShaderProgram("graphicsSource/matVS.glsl", "graphicsSource/simpFS.glsl");
	GLuint texShader = getSP(1);
	glUseProgram(texShader);
	drawBG(sMatrix, sScale, sTrans, sRot, texColor);

	int fx = frameX/2;
	int fy = frameY/2;
	int cx = clamp(centerX, fx, w->x - fx - 1);
	int cy = clamp(centerY, fy, w->y - fy - 1);
	float xSize = 2.0f / frameX;//(float)scr->width / 10000;
	float ySize = 2.0f / frameY;//(float)scr->height /10000;
	sMatrix[0] = 1;//xSize;
	sMatrix[5] = 1;//ySize;
	glUseProgram(texShader);
	glUniformMatrix4fv(sScale, 1, GL_TRUE, sMatrix);
	mat[0] = xSize;
	mat[5] = ySize;
	glUseProgram(baseShader);
	glUniformMatrix4fv(sMat, 1, GL_TRUE, mat);
	glBindVertexArray(squa);
	mat[0] = 1;
	mat[5] = 1;
	//make list for sprite//need to be drawn after solid blocks
	linkedList *animList = makeList();
	linkedList *posList = makeList();//store screen positions of sprites
	for (int x = 0; x < frameX; x++) {
		mat[3] = (-1 + xSize/2) + (x * xSize);
		for (int y = 0; y < frameY; y++) {
			int xp = x + (cx-fx);
			int yp = y + (cy-fy);
			if (xp >= 0 && xp < w->x && yp >= 0 && yp < w->y) {
				Form *f = w->map[xp][yp];
				if (f != NULL) {
					if (f->anim == NULL) {
						glUseProgram(baseShader);
						glBindVertexArray(squa);
						mat[7] = (-1 + ySize/2) + (y * ySize);	
						glUniformMatrix4fv(tMat, 1, GL_TRUE, mat);
						float *fCol = (float*)calloc(3, sizeof(float));
						if (f->id == 10) {
							float *m = getStat(f, "moisture");
							if (m != NULL) {
								float moistMulti = 1 - min(*m, 0.9);// min(1 - ( (f->stat) - 0.1), 1);
								for (int i = 0; i < 3; i++) {
									fCol[i] = f->color[i] * moistMulti;
								}
							}
						}
						glUniform4f(color, fCol[0], fCol[1], fCol[2], 1.0);
						free(fCol);
						glDrawArrays(GL_TRIANGLES, 0, 6);
					} else if (f->anim != NULL && (xp == f->pos[0] && yp == f->pos[1])) {
						addToList(&animList, f);
						int *xPos = (int*)calloc(1, sizeof(int));
						int *yPos = (int*)calloc(1, sizeof(int));
						*xPos = x;
						*yPos = y;
						addToList(&posList, xPos);
						addToList(&posList, yPos);
					}
				}
			}
		}
	}
	glUseProgram(texShader);
	linkedList *curAnim = animList;
	linkedList *curPos = posList;
	int *xPos;
	int *yPos;
	while (curAnim != NULL) {
		if (curAnim->data != NULL) {
			xPos = (int*)(curPos->data);
			curPos = curPos->next;
			if (curPos != NULL) {
				yPos = (int*)(curPos->data);
			} else {
				printf("no yPos\n");
			}
			curPos = curPos->next;
			Form *f = (Form*)(curAnim->data);
			drawFormSprite(f, sMatrix, xSize, ySize, *xPos, *yPos, sScale, sTrans, sRot);
		}
		curAnim = curAnim->next;
	}
	freeListSaveObj(&animList);
	freeList(&posList);
	drawFG(sMatrix, sScale, sTrans, sRot, texColor);
}

void drawFormSprite(Form *f, float *sMatrix, float xSize, float ySize, int xp, int yp, GLuint sScale, GLuint sTrans, GLuint sRot) {
	Anim *a = (Anim*)f->anim;
	float *anim = getStat(f, "anim");
	if (anim != NULL) {
		if (a->sprite != (int)(*anim)) {
			changeSprite(a, (int)*anim);
		} 
	} 
	sMatrix[3] = 0;
	sMatrix[7] = 0;
	sMatrix[0] = xSize * a->scale[0] * convertInvert(f->invert[0]);//a->flip[0];
	sMatrix[5] = ySize * a->scale[1] * convertInvert(f->invert[1]);//a->flip[1];
	glUniformMatrix4fv(sScale, 1, GL_TRUE, sMatrix);
	setSpriteTexture(a);
	sMatrix[3] = (-1 + xSize/2) + (xp * xSize);// + -a->flip[0] * 0.01f;
	sMatrix[7] = (-1 + ySize/2) + (yp * ySize);// + 0.01f;	
	sMatrix[0] = 1;//xSize * a->scale[0] * a->flip[0];
	sMatrix[5] = 1;//ySize * a->scale[1] * a->flip[1];
	glUniformMatrix4fv(sTrans, 1, GL_TRUE, sMatrix);
	float rad = rotoToRadian(f->roto);
	float rMatrix[] = {
		cos(rad), -sin(rad), 0.0, 0.0,
		sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0 ,0.0,
		0.0, 0.0, 0.0, 1.0
	};
	glUniformMatrix4fv(sRot, 1, GL_TRUE, rMatrix);
	//glUniform3f(texColor, 1, 1, 1);

	drawSprite(a, texColor);
}


void drawGrid(float *mat, int tMat, int sMat, int rMat, int color, GLuint vLi) {
	float xSize = 2.0f / frameX;//(float)scr->width / 10000;
	float ySize = 2.0f / frameY;//(float)scr->height /10000;
		float matrix[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
	
	glUniformMatrix4fv(sMat, 1, GL_TRUE, matrix);
	glUniformMatrix4fv(rMat, 1, GL_TRUE, matrix);
	mat[7] = 0;
	glUniform4f(color, 0, 0, 0, 1.0);
	glBindVertexArray(vLi);
	for (int x = 0; x < frameX; x++) {
		mat[3] = -1 + (x * xSize);
		glUniformMatrix4fv(tMat, 1, GL_TRUE, mat);
		glDrawArrays(GL_LINES, 0, 2);	
	}

	mat[3] = 0;
	float rMatrix[] = {
		0, -1, 0, 0,
		1, 0, 0, 0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	glUniformMatrix4fv(rMat, 1, GL_TRUE, rMatrix);
	for (int y = 0; y < frameY; y++) {
		mat[7] = -1 + (y * ySize);
		glUniformMatrix4fv(tMat, 1 ,GL_TRUE, mat);
		glDrawArrays(GL_LINES, 0, 2);
	}
}

void setCenter(float cp[2]) {
	centerX = cp[0];
	centerY = cp[1];
}

void setFrame(int x, int y) {
	frameX = x;
	frameY = y;
}

void setAnim(Form *f, Anim *a) {
	f->anim = a;
	addAnim(a);
}

void setGrid(bool state) {
	gridOn = state;
}

void togglePause(void *, float poo) {
	if (poo > 0) {
		paused = !paused;
	}
}

void toggleGod(void *, float poo) {
	if (poo > 0) {
		if (godMode) {
			setCenter(pooper->me->body->pos);
			setFrame(100, 100);
			godMode = false;
		} else {
			setCenter(godPos);
			setFrame(getWorld()->x, getWorld()->y);
			godMode= true;
		}
	}
}

void exitGame() {
	printf("exiting\n");
	freeBG();
	freeFG();
	freePlayerManager();
	deleteAnimList();
	deleteTextureManager();
	free(godPos);
	freeWorld();
	freeJoyList();
	freeInput();
	glfwTerminate();
}
