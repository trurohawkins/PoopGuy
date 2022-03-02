#include "FormGlfw.h"
#include "Player.c"
#include "Camera.c"
#include "DrawWorld.c"
#include "../actor/Cloud.c"
#include "../controllerDB.c"

Camera *cam;
float centerX;
float centerY;
int frameX = 50;
int frameY = 50;
int defaultFrameY = -1;
int defaultFrameX = -1;
PoopGuy **poopers;
int numPlayers = 1;
bool gridOn = false;
bool paused = false;
bool godMode = false;
bool debugDraw = false;
float *godPos;
Menu *pauseMenu;
GOD *god = 0;

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
	GLuint tileShader = getSP(2);
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
		cam = getDefaultCam();
		glUseProgram(baseShader);
		glUniformMatrix4fv(rMat, 1, GL_TRUE, matrix);
		World *w = getWorld();
		makePlayerManager();
		makeActorList();
		makeAnimList();
		makeTextureManager();
		initUILists();

		makeStoneSquare((w->x/2), (w->y/2) - 40, 10);
		poopers = (PoopGuy **)calloc(numPlayers, sizeof(PoopGuy*));	
		for (int i = 0; i < numPlayers; i++) {
			poopers[i] = makePoopPlayer((w->x * 0.95) + (i*4), 1, i);
		}
		//set up offsets for rendering instances
		glUseProgram(tileShader);
		initTileSets();
		//cloud = makeGhost("resources/cloud.png", 1, 1, 1, tcTrans, tcScale);
		Button *demonButt = makeButton("resources/demonghost.png", 0, 2, 1, tmpButtFunc);
		Button *faceButt = makeButton("resources/faceghost.png", 0, 2, 1, exitMenu);
		Text *resume = makeText("RESUME", 1, true, 1, 1, 1);
		addText(faceButt->graphics, resume);
		Text *exit = makeText("EXIT", 1, true, 1, 1, 1);
		addText(demonButt->graphics, exit);
		placeUI(demonButt->graphics, -0.5, 0);
		placeUI(faceButt->graphics, 0.5, 0);
		pauseMenu = makeMenu(50);
		addButton(pauseMenu, demonButt);
		addButton(pauseMenu, faceButt);
		//addBackground(cloud2);
		//addForeground(cloud2);
		makeCloud(10, 50, 20);
		
		Anim *dirt = makeAnimSheet("resources/dirtTileSheet.png", 1, 15, 5);
		GLuint sv = makeSpriteVao(1,1);
		animAddVao(dirt, sv);

		Anim *stone = makeAnimSheet("resources/rockSheet.png", 1, 15, 1);
		GLuint ss = makeSpriteVao(1,1);
		animAddVao(stone, ss);
		TileSet *dirtTiles = makeTileSet(dirt, cam->frameX, cam->frameY, w->x, w->y);
		TileSet *stoneTiles = makeTileSet(stone, cam->frameX, cam->frameY, w->x, w->y);

		glfwUpdateGamepadMappings(gamecontrollerdb);
		//free(mappings);
		god = makeGodPlayer(w->x/2, w->y/2, cam->frameX, cam->frameY);
		Player *nullPlayer = makePlayer(NULL, -1, NULL);
		addControl(nullPlayer, "K0G", toggleGod);
		addControl(nullPlayer, "K0!", togglePauseMenu);//S
		addControl(nullPlayer, "J07", togglePauseMenu);
		addControl(nullPlayer, "K0B", toggleDebugDraw);//B for Boxes
		godPos =  (float*)calloc(2, sizeof(float));
		godPos[0] = getWorld()->x /2;
		godPos[1] = getWorld()->y /2;
		setCenter(cam, godPos);
		//glUseProgram(texShader);
		float xSize = 2.0f / frameX;//(float)scr->width / 10000;
		float ySize = 2.0f / frameY;//(float)scr->height /10000;
		float sMatrix[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
		//toggleGod(0, 1);
		//debugDraw = true;
		while(!glfwWindowShouldClose(screen->window)) {
			glfwPollEvents();
			checkControllerInput();
			processKeys();
			if(glfwGetKey(screen->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				//glfwSetWindowShouldClose(screen->window, 1);
			}
			if (!paused) {
				AnimListAnimate();
				actorListDo();
				groundWater();
				if (!godMode && poopers[0] != NULL) {
					setCenter(cam, poopers[0]->me->body->pos);
					//printf("currently at %f, %f\n", pooper->me->body->pos[0], pooper->me->body->pos[1]);
				} else if (god == NULL) {
					setCenter(cam, godPos);
				}
		
				glClearColor(0.1, 0.2, 0.4, 1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				if (debugDraw) {
					drawWorldDebug(w, cam, tMat, sMat, rMat, drawColor, squa);
				} else {
					//glUseProgram(texShader);
					drawWorld(w, cam);
				}
				if (gridOn) {
					glUseProgram(baseShader);
					drawGrid(matrix, tMat, sMat, rMat, drawColor, vLi);
				}
				//drawText(exit, 25, 25);
				//drawText(resume, 100, 100);
				//renderText("YONNI", screen->width/2, screen->height/2, 1);		
				//renderText("POOPGUY", 25, 25, 1);		
				glfwSwapBuffers(screen->window);
			
			} else {
				glClearColor(0.1, 0.1, 0.1, 1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glUseProgram(texShader);
				drawPause(sMatrix);
				updateMenu();
				glfwSwapBuffers(screen->window);
			}
			
		}
		exitGame();
	}
}
void drawWorldOld(World *w, int tMat, int sMat, int rMat, int color, GLuint squa) {
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
				Form** residents = getCellContents(w->map[xp][yp]);
				if (residents != NULL) {
					for (int i = 0; i < w->map[xp][yp]->count; i++) {
						Form *f = residents[i];//checkSolidForm(w->map[xp][yp]);
						if (f != NULL) {
							float xfp = f->pos[0] - (cx-fx);//x + (cx-fx);
							float yfp = f->pos[1] - (cy-fy);
							float *tile = getStat(f, "tile");
							if (tile != NULL) {
								//addFormToAnim(back, f, tileSet, xfp, yfp);
							} else if (f->anim == NULL) {
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
								//printf("form at %f, %f\n", xfp, yfp);
								//printf("adding  %i, %i\n", x, y);
								Anim *a = (Anim*)f->anim;
								if (a->drawOrder > 0) {
									addFormToAnim(front, f, 0, xfp, yfp);
								} else if (a->drawOrder < 0) {
									addFormToAnim(back, f, 0, xfp, yfp);
								} else {
									addFormToAnim(mid, f, 0, xfp, yfp);
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
	//drawAnimOrder(front, sMatrix, xSize, ySize);
	freeAnimOrder(back);
	freeAnimOrder(front);
	freeAnimOrder(mid);
	drawFG(sMatrix);
}

void setAnim(Form *f, Anim *a) {
	f->anim = a;
	addAnim(a);
}

void setGrid(bool state) {
	gridOn = state;
}

void drawGrid(float *mat, int tMat, int sMat, int rMat, int color, GLuint vLi) {
	float xSize = 2.0f / cam->frameX;//(float)scr->width / 10000;
	float ySize = 2.0f / cam->frameY;//(float)scr->height /10000;
		float matrix[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
	
	glUniformMatrix4fv(sMat, 1, GL_TRUE, matrix);
	glUniformMatrix4fv(rMat, 1, GL_TRUE, matrix);
	mat[7] = 0;
	glUniform4f(color, 0, 0, 0, 0.4);
	glBindVertexArray(vLi);
	for (int x = 0; x < cam->frameX; x++) {
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
	for (int y = 0; y < cam->frameY; y++) {
		mat[7] = -1 + (y * ySize);
		glUniformMatrix4fv(tMat, 1 ,GL_TRUE, mat);
		glDrawArrays(GL_LINES, 0, 2);
	}
}

void exitMenu() {
	paused = false;
	setMenuActive(pauseMenu, false);
	getMouseBack();
}

void togglePauseMenu(void *, float poo) {
	if (poo > 0) {
		paused = !paused;
		setMenuActive(pauseMenu, paused);
		if (!paused) {
			getMouseBack();
		}
	}
}

void toggleDebugDraw(void *, float poo) {
	if (poo > 0) {
		debugDraw = !debugDraw;
	}
}

void toggleGod(void *, float poo) {
	if (poo > 0) {
		printf("toggle god %i\n", godMode);
		if (godMode) {
			godOff(god);
			if (poopers[0] != NULL) {
				setCenter(cam, poopers[0]->me->body->pos);
			}
			setFrame(cam, cam->defaultFrameX, cam->defaultFrameY);
			for (int i = 0; i < getTileCount(); i++) {
				TileSet *ts = getTile(i);
				resizeTileSet(ts, cam->defaultFrameX, cam->defaultFrameY);
			}
			godMode = false;
		} else {
			godMode= true;
			setGod(god, cam->centerX, cam->centerY, cam->frameX, cam->frameY);
			godOn(god);
		}

	}
}

void exitGame() {
	printf("exiting\n");
	freeUILists();
	deleteAnimList();
	deleteTextureManager();
	free(godPos);
	freePlayerManager();
	freeWorld();
	freeJoyList();
	freeInput();
	glfwTerminate();
}
