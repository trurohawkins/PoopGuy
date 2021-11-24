#include "FormGlfw.h"
#include "Player.h"
#include "poopPlayer.c"

float centerX;
float centerY;
int frameX = 50;
int frameY = 50;
bool gridOn = false;
bool paused;
bool godMode = false;
PoopGuy *pooper;
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
		Anim *poo = makeAnim("resources/poopGuySpriteSheet.png", 4, 6, tcTrans, tcScale);
		setScale(poo, 4, 4);
		for (int i = 1; i < 4; i++) {
			addSprite(poo, i, 6);
		}
		GLuint spriteVao = makeSpriteVao(1, 1);
		animAddVao(poo, spriteVao);//makeSpriteVao(1, 1));
		setAnim(pooper->me->body, poo);
		Player *pPlayer = makePlayer(pooper->me, poo);
		makePoopPlayer(pPlayer, pooper);
		char *mappings = fileToString("gamecontrollerdb.txt");
		const char *cMap = (const char*)mappings;
		glfwUpdateGamepadMappings(cMap);
		free(mappings);
		addControl(pPlayer,"K0G", toggleGod);
		godPos =  (float*)calloc(2, sizeof(float));
		godPos[0] = getWorld()->x /2;
		godPos[1] = getWorld()->y /2;

		while(!glfwWindowShouldClose(screen->window)) {
			glfwPollEvents();
			checkControllerInput();
			processKeys(pPlayer);
			if(glfwGetKey(screen->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(screen->window, 1);
			}
			if (!paused) {
				animate(poo);
				actorListDo();
				if (!godMode) {
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
		freePlayer(pPlayer);
		freeAnim(poo);
		free(godPos);
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
							float moistMulti = min(1 - ( (f->stat / 10) - 0.3), 1);
							for (int i = 0; i < 3; i++) {
								fCol[i] = f->color[i] * moistMulti;
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
}

void drawFormSprite(Form *f, float *sMatrix, float xSize, float ySize, int xp, int yp, GLuint sScale, GLuint sTrans, GLuint sRot) {
	Anim *a = (Anim*)f->anim;
	//sMatrix[3] = (-1 + xSize/2) + (xp * xSize);
	//sMatrix[7] = (-1 + ySize/2) + (yp * ySize);	
	sMatrix[0] = xSize * a->scale[0] * a->flip[0];
	sMatrix[5] = ySize * a->scale[1] * a->flip[1];
	glUniformMatrix4fv(sScale, 1, GL_TRUE, sMatrix);
	setSpriteTexture(a);
	sMatrix[3] = (-1 + xSize/2) + (xp * xSize);// + -a->flip[0] * 0.01f;
	sMatrix[7] = (-1 + ySize/2) + (yp * ySize);// + 0.01f;	
	sMatrix[0] = 1;//xSize * a->scale[0] * a->flip[0];
	sMatrix[5] = 1;//ySize * a->scale[1] * a->flip[1];
	glUniformMatrix4fv(sTrans, 1, GL_TRUE, sMatrix);
	float rad = rotoToRadian(a->roto);
	float rMatrix[] = {
		cos(rad), -sin(rad), 0.0, 0.0,
		sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0 ,0.0,
		0.0, 0.0, 0.0, 1.0
	};
	glUniformMatrix4fv(sRot, 1, GL_TRUE, rMatrix);
	drawSprite(a);
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
/*
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		//printf("key press = %i\n", key);
		if (key == 96) {
			paused = !paused;
		}
		keyPressPoopGuy(getPoopGuy(), key);
	} else if (action == GLFW_RELEASE) {
		keyReleasePoopGuy(getPoopGuy(), key);
	}
}
*/
void setCenter(float cp[2]) {
	centerX = cp[0];
	centerY = cp[1];
}

void setFrame(int x, int y) {
	frameX = x;
	frameY = y;
}

void setGrid(bool state) {
	gridOn = state;
}

void toggleGod(float poo) {
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
	deletePoopGuy(pooper);
	freeWorld();
	freeJoyList();
	freeInput();
	glfwTerminate();
}
