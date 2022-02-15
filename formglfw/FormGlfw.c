#include "FormGlfw.h"
#include "Player.c"
#include "../actor/Cloud.c"
#include "../controllerDB.c"

float centerX;
float centerY;
int frameX = 50;
int frameY = 50;
PoopGuy *pooper;
int numPlayers = 1;
bool gridOn = false;
bool paused = false;
bool godMode = false;
float *godPos;

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
		initTexInts(texShader);
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
		float matrix[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
		glUseProgram(baseShader);
		glUniformMatrix4fv(rMat, 1, GL_TRUE, matrix);
		World *w = getWorld();
		makePlayerManager();
		makeActorList();
		makeAnimList();
		makeTextureManager();
		initBackgroundUI();
		initForegroundUI();
		for (int i = 0; i < numPlayers; i++) {
			PoopGuy* tmp = makePoopPlayer(2 + (i*4), w->y - 3, i);
			if (i == 0) {
				pooper = tmp;
			}
		}
		//cloud = makeGhost("resources/cloud.png", 1, 1, 1, tcTrans, tcScale);
		UI *cloud2 = makeUI("resources/demonghost.png", 0, 1, 1);
		//addBackground(cloud);
		addForeground(cloud2);
		makeCloud(10, 50, 20);
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
					//printf("currently at %f, %f\n", pooper->me->body->pos[0], pooper->me->body->pos[1]);
				} else {
					setCenter(godPos);
				}
			}
			glClearColor(0.1, 0.2, 0.4, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			if (gridOn) {
				drawGrid(matrix, tMat, sMat, rMat, drawColor, vLi);
			}
			drawWorld(w, tMat, sMat, rMat, drawColor, squa);
			glfwSwapBuffers(screen->window);
		}
		exitGame();
	}
}

void drawWorld(World *w, int tMat, int sMat, int rMat, int color, GLuint squa) {
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
	drawBG(sMatrix);

	int fx = frameX/2;
	int fy = frameY/2;
	int cx = clamp(centerX, fx, w->x - fx - 1);
	int cy = clamp(centerY, fy, w->y - fy - 1);
	float xSize = 2.0f / frameX;//(float)scr->width / 10000;
	float ySize = 2.0f / frameY;//(float)scr->height /10000;
	mat[0] = xSize;
	mat[5] = ySize;
	glUseProgram(baseShader);
	glUniformMatrix4fv(sMat, 1, GL_TRUE, mat);
	glBindVertexArray(squa);
	mat[0] = 1;
	mat[5] = 1;
	//make list for sprite//need to be drawn after solid blocks
	AnimOrder *back = makeAnimOrder(-1);
	AnimOrder *mid = makeAnimOrder(0);
	AnimOrder *front = makeAnimOrder(1);
	//printf("vewing %i, %i to %i, %i\n", cx-fx, cy-fy, frameX+(cx-fx), frameY+(cy-fy));
	for (int x = 0; x < frameX; x++) {
		mat[3] = (-1 + xSize/2) + (x * xSize);
		for (int y = 0; y < frameY; y++) {
			int xp = x + (cx-fx);
			int yp = y + (cy-fy);
			if (xp >= 0 && xp < w->x && yp >= 0 && yp < w->y) {
				Form** residents = getContents(w->map[xp][yp]);
				if (residents != NULL) {
					for (int i = 0; i < w->map[xp][yp]->count; i++) {
						Form *f = residents[i];//checkSolidForm(w->map[xp][yp]);
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
							} else if (f->anim != NULL && (xp == (int)(floor(f->pos[0])) && yp == (int)(floor(f->pos[1])))) {
								float xfp = f->pos[0] - (cx-fx);//x + (cx-fx);
								float yfp = f->pos[1] - (cy-fy);
								//printf("form at %f, %f\n", xfp, yfp);
								//printf("adding  %i, %i\n", x, y);
								Anim *a = (Anim*)f->anim;
								if (a->drawOrder > 0) {
									addFormToAnim(front, f, xfp, yfp);
								} else if (a->drawOrder < 0) {
									addFormToAnim(back, f, xfp, yfp);
								} else {
									addFormToAnim(mid, f, xfp, yfp);
								}
							}
						}
					}
					free(residents);
				}
			}
		}
	}
	glUseProgram(texShader);
	drawAnimOrder(back, sMatrix, xSize, ySize);
	drawAnimOrder(mid, sMatrix, xSize, ySize);
	drawAnimOrder(front, sMatrix, xSize, ySize);
	freeAnimOrder(back);
	freeAnimOrder(front);
	freeAnimOrder(mid);
	drawFG(sMatrix);
}

AnimOrder *makeAnimOrder(int order) {
	AnimOrder *ao = (AnimOrder*)calloc(sizeof(AnimOrder), 1);
	ao->anims = makeList();
	ao->poses = makeList();
	ao->order = order;
}

void addFormToAnim(AnimOrder *ao, Form *f, float x, float y) {
	addToList(&(ao->anims), f);
	float *xPos = (float*)calloc(1, sizeof(float));
	float *yPos = (float*)calloc(1, sizeof(float));
	*xPos = x;
	*yPos = y;
	addToList(&(ao->poses), xPos);
	addToList(&(ao->poses), yPos);
}

void drawAnimOrder(AnimOrder *ao, float *sMatrix, float xSize, float ySize) {
	linkedList *curAnim = ao->anims;//animList;
	linkedList *curPos = ao->poses;//posList;
	float *xPos;
	float *yPos;
	while (curAnim != NULL) {
		if (curAnim->data != NULL) {
			xPos = (float*)(curPos->data);
			curPos = curPos->next;
			if (curPos != NULL) {
				yPos = (float*)(curPos->data);
			} else {
				printf("no yPos\n");
			}
			curPos = curPos->next;
			Form *f = (Form*)(curAnim->data);
			drawSprite((Anim*)f->anim, sMatrix, xSize, ySize, *xPos, *yPos);
		}
		curAnim = curAnim->next;
	}
}

void freeAnimOrder(AnimOrder *ao) {
	freeListSaveObj(&(ao->anims));
	freeList(&(ao->poses));
	free(ao);
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

void togglePause(void *, float poo) {
	if (poo > 0) {
		paused = !paused;
	}
}

void toggleGod(void *, float poo) {
	if (poo > 0) {
		if (godMode && numPlayers > 0) {
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
	deleteAnimList();
	deleteTextureManager();
	free(godPos);
	freePlayerManager();
	freeWorld();
	freeJoyList();
	freeInput();
	glfwTerminate();
}
