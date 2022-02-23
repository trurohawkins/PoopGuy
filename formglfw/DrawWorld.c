#include "DrawWorld.h"
Camera *curCam = 0;

void drawWorld(World *w, Camera *cam) {
	if (curCam == 0) {
		curCam = cam;
	}
	int fx = cam->frameX/2;
	int fy = cam->frameY/2;
	int cx = clamp(cam->centerX, fx, w->x - fx);
	int cy = clamp(cam->centerY, fy, w->y - fy);
	AnimOrder *back = makeAnimOrder(-1);
	AnimOrder *mid = makeAnimOrder(0);
	AnimOrder *front = makeAnimOrder(1);
	float xSize = 2.0f / cam->frameX;//(float)scr->width / 10000;
	float ySize = 2.0f / cam->frameY;//(float)scr->height /10000;
	float sMatrix[] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	GLuint texShader = getSP(1);
	GLuint tileShader = getSP(2);
	linkedList *tileList = makeList();
	glUseProgram(tileShader);
	int tileSeen = 0;
	//printf("\n\n");
	for (int x = 0; x < cam->frameX; x++) {
		for (int y = 0; y < cam->frameY; y++) {
			int xp = x + (cx-fx);
			int yp = y + (cy-fy);
			if (xp >= 0 && xp < w->x && yp >= 0 && yp < w->y) {
				Cell *cur = w->map[xp][yp];
				Form** residents = getCellContents(cur);
				if (residents != NULL) {
					for (int i = 0; i < cur->count; i++) {
						//if (residents != NULL) {
						Form *f = residents[i];
						if (f != NULL) {
							float xfp = f->pos[0] - (cx-fx);//x + (cx-fx);
							float yfp = f->pos[1] - (cy-fy);
							float *tile = getStat(f, "tile");
							//printf("- %i -\n", f->id);
							if (tile != NULL) {
								int *ts = (int*)calloc(sizeof(int), 1);
								*ts = (int)(*tile);			
								TileSet *t = getTile(*ts);
								float remainder = *tile - *ts;
								if (t != NULL) {
									if (t->typeID == -1) {
										setTileSetID(t, f->id);
									}
									if (!isInListInt(&tileList, *ts)) {
										tileSeen++;
										addToList(&tileList, ts);
										clearData(t->trans, false);
										//clearData(t->texture, true);
										setRots(t->rot, 0);
										//setData(t->color, 1);
									} else {
										free(ts);
									}
									editData(t->trans, x, y, 1, 1);
								} else {
									free(ts);
								}
								tileCell(t, remainder, xp, yp);
								float *m = getStat(f, "moisture");
								if (m != NULL) {
									float moistMulti = 1 - min(*m, 0.9);// min(1 - ( (f->stat) - 0.1), 1);
									editData(t->color, x, y, moistMulti, 4);
									editData(t->color, x, y, moistMulti, 3);
									editData(t->color, x, y, moistMulti, 2);
									editData(t->color, x, y, 1, 1);
								}
								//printf(" %i ", 1);
								//editTranslations(x, y, 0);
							} else {
								//editData(ds, x, y, 0, 2);
								//printf(" %i ", 0);
 								if (f->anim != NULL && (xp == (int)(floor(f->pos[0])) && yp == (int)(floor(f->pos[1])))) {
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
					}
				}
				free(residents);
				//editData(ds, x, y, 1.8333, 1);
			} else {
				//editData(ds, x, y, 0, 2);
			}
		}
		//printf("\n");
	}
		//printf("\n");
	//printData(ds);
	float mat[] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	glUseProgram(texShader);
	drawBG(sMatrix);
	drawAnimOrder(back, mat, xSize, ySize);
	if (tileSeen > 0) {
		glUseProgram(tileShader);
		void **tileSets = getContents(&tileList, tileSeen);
		for (int i = 0; i < tileSeen; i++) {
			int cur = *((int*)tileSets[i]);
			//printf("drawing set for %i\n", cur);
			TileSet *tmp = getTile(cur);
			setTileVBO(tmp);
			setUpTiles(tmp->set, sMatrix, xSize, ySize);
			//tileData(tmp, w);
			bindData(tmp->trans);
			bindData(tmp->rot);
			bindData(tmp->color);
			bindData(tmp->texture);
			glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, cam->frameX * cam->frameY);
		}
		free(tileSets);
	}
	freeList(&tileList);
	glUseProgram(texShader);
	//bindVertexArray(squa);
	drawAnimOrder(mid, mat, xSize, ySize);
	drawAnimOrder(front, mat, xSize, ySize);
	freeAnimOrder(back);
	freeAnimOrder(front);
	freeAnimOrder(mid);
	drawFG(sMatrix);
}

void tileCell(TileSet *t, float remainder, int x, int y) {
	int **d = getDirs();
	DrawScreen *ds = t->texture;
	DrawScreen *rot = t->rot;
	World *w = getWorld();
	int fx = curCam->frameX/2;
	int fy = curCam->frameY/2;
	int cx = clamp(curCam->centerX, fx, w->x - fx - 1);
	int cy = clamp(curCam->centerY, fy, w->y - fy - 1);
	int id = getFormID(x, y);
	//if (getData(ds, x, y, 2) == 1) {
	if (id == t->typeID) {
		//printf("%i, %i - got type id %i\n", x, y, id);
		int mostOpen = -1;
		int start = 0;
		int startSide = start;
		for (int i = 0; i < 4; i++) {
			int openSides = 0;
			start = (start + i) % 4;
			for (int j = 0; j < 4; j++) {
				int cur = (start + j) % 4;
				//printf("  from dir: %i got %i, %i\n", cur, d[cur][0], d[cur][1]);
				//printf("    ergo checking %i, %i\n", x + d[cur][0], y + d[cur][1]);
				//if (getData(ds, x + d[cur][0], y + d[cur][1], 2) == 0) {
				if (getFormID(x + d[cur][0], y + d[cur][1]) != t->typeID) {
					openSides++;
				} else {
					//printf("got %i\n",getFormID(x + d[cur][0], y + d[cur][1] 
					//printf("break\n");
					break;
				}
			}
			if (openSides > mostOpen) {
				mostOpen = openSides;
				startSide = start;
			}
		}

		if (mostOpen == 1) {
			int oppoSide = (startSide + 2) % 4;
			//if (getData(ds, x + d[oppoSide][0], y + d[oppoSide][1], 2) == 0) {
			if (getFormID(x + d[oppoSide][0], y + d[oppoSide][1]) != t->typeID) {
				mostOpen = 5;
			} else {
				int **d8 = getDir8();
				int nextCorn = ((startSide*2) + 3) % 8;
				int preCorn = ((startSide*2) + 5) % 8;
				//float nc = getData(ds, x + d8[nextCorn][0], y + d8[nextCorn][1], 2);
				float nc = getFormID(x + d8[nextCorn][0], y + d8[nextCorn][1]);
				//float pc = getData(ds, x + d8[preCorn][0], y + d8[preCorn][1], 2);
				float pc = getFormID(x + d8[preCorn][0], y + d8[preCorn][1]);
				if (nc != t->typeID && pc != t->typeID) {
					mostOpen = 13;
				} else if (nc != t->typeID){ 
					mostOpen = 11;
				} else if (pc != t->typeID) {
					mostOpen = 12; 
				}
			}
		} else if (mostOpen == 2) {
				int **d8 = getDir8();
				int oppoCorn = ((startSide*2) + 5) % 8;
				//if (getData(ds, x + d8[oppoCorn][0], y + d8[oppoCorn][1], 2) == 0) {
				if (getFormID(x + d8[oppoCorn][0], y + d8[oppoCorn][1]) != t->typeID) {
					mostOpen = 14;
				}
		} else if (mostOpen == 0) {
			int **d8 = getDir8();
			int check = 0;
			int mostCorn = -1;
			start = 7;
			int s = 7;
			for (int i = 0; i < 4; i++) {
				int corners = 0;
				start = (s + (i * 2)) % 8;
				for (int j = 0; j < 4; j++) {
					int cur = (start + (j * 2)) % 8;
					//if (getData(ds, x + d8[cur][0], y + d8[cur][1], 2) == 0) {
					if (getFormID(x + d8[cur][0], y + d8[cur][1]) != t->typeID) {
						corners++;
					} else {
						break;
					}
				}
				if (corners > mostCorn) {
					check = i;
					mostCorn = corners;
				}
			}
			if (mostCorn != 0) {
				mostOpen = 6 + (mostCorn -1);
				startSide = check;
			}
		}

		//printf("mostOpen: %i and startSide: %i\n", mostOpen, startSide);
		float texVal = (t->set->spriteNum-1 - mostOpen) * (t->set->frameY)+1; 
		float texValX = (int)(round(remainder * (t->set->length[0] - 1))) * t->set->frameX;
		editData(ds, x -(cx-fx), y - (cy-fy), texVal, 1);
		//printf("X value: %f\n", getData(ds, x - (cx-fx), y - (cy-fy), 2));
		editData(ds, x -(cx-fx), y - (cy-fy), texValX, 2);
		setRot(rot, x - (cx-fx), y - (cy-fy), dirToRad(startSide));
	}
}

AnimOrder *makeAnimOrder(int order) {
	AnimOrder *ao = (AnimOrder*)calloc(sizeof(AnimOrder), 1);
	ao->anims = makeList();
	ao->poses = makeList();
	ao->order = order;
}

void addFormToAnim(AnimOrder *ao, Form *f, Anim *anim, float x, float y) {
	if (anim == NULL) {
		anim = (Anim*)f->anim;
	}
	
	addToList(&(ao->anims), anim);
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
			Anim *a = (Anim*)(curAnim->data);
			drawSprite(a, sMatrix, xSize, ySize, *xPos, *yPos);
		}
		curAnim = curAnim->next;
	}
}

void freeAnimOrder(AnimOrder *ao) {
	freeListSaveObj(&(ao->anims));
	freeList(&(ao->poses));
	free(ao);
}

void drawWorldDebug(World *w, Camera *cam, int tMat, int sMat, int rMat, int color, GLuint squa) {
		float mat[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
		float rMatrix[] = {
			cos(0), -sin(0), 0.0, 0.0,
			sin(0), cos(0), 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
	GLuint baseShader = getSP(0);//makeShaderProgram("graphicsSource/matVS.glsl", "graphicsSource/simpFS.glsl");
	int fx = cam->frameX/2;
	int fy = cam->frameY/2;
	int cx = clamp(cam->centerX, fx, w->x - fx);
	int cy = clamp(cam->centerY, fy, w->y - fy);
	float xSize = 2.0f / cam->frameX;//(float)scr->width / 10000;
	float ySize = 2.0f / cam->frameY;//(float)scr->height /10000;
	glUseProgram(baseShader);
	glUniformMatrix4fv(rMat, 1, GL_TRUE, rMatrix);
	mat[0] = xSize;
	mat[5] = ySize;
	glUniformMatrix4fv(sMat, 1, GL_TRUE, mat);
	glBindVertexArray(squa);
	mat[0] = 1;
	mat[5] = 1;
	for (int x = 0; x < cam->frameX; x++) {
		mat[3] = (-1 + xSize/2) + (x * xSize);
		for (int y = 0; y < cam->frameY; y++) {
			int xp = x + (cx-fx);
			int yp = y + (cy-fy);
			if (xp >= 0 && xp < w->x && yp >= 0 && yp < w->y) {
				Form *f = checkSolidForm(w->map[xp][yp]);
				if (f != NULL) {
					//float xfp = f->pos[0] - (cx-fx);//x + (cx-fx);
					//float yfp = f->pos[1] - (cy-fy);
					//glBindVertexArray(squa);
					mat[7] = (-1 + ySize/2) + (y * ySize);	
					glUniformMatrix4fv(tMat, 1, GL_TRUE, mat);
					float *m = getStat(f, "moisture");
					if (m != NULL) {
						float *fCol = (float*)calloc(3, sizeof(float));
						float moistMulti = 1 - min(*m, 0.9);// min(1 - ( (f->stat) - 0.1), 1);
						for (int i = 0; i < 3; i++) {
							fCol[i] = f->color[i] * moistMulti;
						}
						glUniform4f(color, fCol[0], fCol[1], fCol[2], 1.0);
						free(fCol);
					} else {
						glUniform4f(color, f->color[0], f->color[1], f->color[2], 1.0);
					}
					glDrawArrays(GL_TRIANGLES, 0, 6);
				}
			}
		}
	}
}

