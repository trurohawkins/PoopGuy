#include "Tile.h"

float *translations;
int dim;
linkedList *TileSets;
int tileCount = 0;
GLuint tileVAO = 0;

void initTileSets() {
	TileSets = makeList();
	tileVAO = makeSpriteVao(1, 1);
}

TileSet *makeTileSet(Anim *a, int xd, int yd, int mx, int my) {
	TileSet *ts = (TileSet*)calloc(sizeof(TileSet), 1);
	ts->set = a;
	ts->typeID = -1;
	GLuint tileShader = getSP(2);
	glUseProgram(tileShader);
	//printf("diemnsions recieved %i, %i\n", xd, yd);
	ts->color = makeDrawScreen(xd, yd, mx, my, 1, 4, true);
	ts->trans = makeDrawScreen(xd, yd, mx, my, 3, 3, false);
	ts->rot = makeDrawScreen(xd, yd, mx, my, 4, 4, true);
	ts->texture = makeDrawScreen(xd, yd, mx, my, 5, 2, true);
	addTileSet(ts);
	return ts;
}

void setTileVBO(TileSet *ts) {
	setScreenVBO(ts->trans);
	setScreenVBO(ts->rot);
	setScreenVBO(ts->color);
	setScreenVBO(ts->texture);
}

int addTileSet(TileSet *t) {
	addToList(&TileSets, t);
	return tileCount++;
}

TileSet *getTile(int index) {
	TileSet *ts = (TileSet*)indexList(&TileSets, index);
	if (ts == NULL) {
		printf("no good NULL tilesset\n");
	}
}

int getTileCount() {
	return tileCount;
}

DrawScreen *makeDrawScreen(int dimensionX ,int dimensionY, int maxDimensionX ,int maxDimensionY, int location, int stride, bool base) {
	DrawScreen *ds = (DrawScreen*)calloc(sizeof(DrawScreen), 1);
	ds->maxX = maxDimensionX;
	ds->maxY = maxDimensionY;
	ds->data = (float*)calloc(sizeof(float), (maxDimensionX) * (maxDimensionY) * stride);
	ds->stride = stride;
	ds->location = location;

	sizeDrawScreen(ds, dimensionX, dimensionY, base, dimensionX < maxDimensionX, dimensionY < maxDimensionY);
	/*
	if (dimensionX > maxDimensionX) {
		ds->ratioX = (float)maxDimensionX / dimensionX; 
		dimensionX = maxDimensionX;
	} else {
		ds->ratioX = 1;
	}
	if (dimensionY > maxDimensionY) {
		ds->ratioY = (float)maxDimensionY / dimensionY;
		dimensionY = maxDimensionY;
	} else {
		ds->ratioY = 1;
	}
	ds->dimensionX = dimensionX;// + 1;
	ds->dimensionY = dimensionY;// + 1;
	initializeData(ds, base);
	glGenBuffers(1, &(ds->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, ds->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ((dimensionX ) * (dimensionY ) * stride), &translations[0], GL_STATIC_DRAW);
	*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return ds;
}

void sizeDrawScreen(DrawScreen *ds, int newSizeX, int newSizeY, bool base, bool bufferedX, bool bufferedY) {
	//printf("resizing tile sets\n");
	if (newSizeX > 0 && newSizeY > 0) {// && newSizeX <= ds->maxX && newSizeY <= ds->maxY) {
		if (bufferedX) {// && newSizeY < ds->maxY) {
			ds->buffX = 1;
		} else {
			ds->buffX = 0;
		}
		if (bufferedY) {
			ds->buffY = 1;
		} else {
			ds->buffY = 0;
		}
		/*
		if (newSizeX >= ds->maxX) {
			ds->ratioX = (float)ds->maxX / newSizeX; 
			newSizeX = ds->maxX;
			ds->buffX = 0;
		} else {
			ds->ratioX = 1;
			ds->buffX = 1;
		}
		if (newSizeY >= ds->maxY) {
			ds->ratioY = (float)ds->maxY / newSizeY;
			newSizeY = ds->maxY;
			ds->buffY = 0;
		} else {
			ds->ratioY = 1;
			ds->buffY = 1;
		}
		*/
		//printf("ratio %f, %f\n", ds->ratioX, ds->ratioY);
		ds->dimensionX = newSizeX;
		ds->dimensionY = newSizeY;
		initializeData(ds, base);
		glGenBuffers(1, &(ds->vbo));
		glBindBuffer(GL_ARRAY_BUFFER, ds->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ((ds->dimensionX) * (ds->dimensionY) * ds->stride), &((ds->data)[0]), GL_STATIC_DRAW);
		setScreenVBO(ds);
	}

}

void initializeData(DrawScreen *ds, bool base) {
	int index = 0;
	if (base) {
		for (int y = -ds->dimensionY; y < ds->dimensionY; y+=2) { 
			for (int x = -ds->dimensionX; x < ds->dimensionX; x+=2) {
					(ds->data)[index++] = 1;	
			}
		}
	} else {
		//printf("poo %f\n", sizeX);
		//0.02
		float xs = ds->sizeX;// * ds->ratioX;
		float ys = ds->sizeY;/// * ds->ratioY;
		float pooX = 0.5;//0.5;
		if (ds->dimensionX % 2 != 0) {
			pooX = 0;
			//ds->buffX = 1;//-1;//0.25;
		} else {
			ds->buffX = 0;
		}
		if (ds->dimensionY % 2 != 0) {
			ds->buffY = 0;//0.5;
		} else {
			ds->buffY = 1;
		}
		//float spx = ds->buffX * (xs);//-1;
		//float spy = ds->buffY * (ys);//0;//-1;
		float startX = -1 + (xs * 0.5);// + (xs * pooX);//((xs / 2) * pooX); // - spx;// - xs/2;//-0.995;
		float startY = -1 + (ys * 0.5);// + ((ys / 2) * ds->buffY);// - spy;// - ys/2;//-0.995;
		//printf("starting indexes %f, %f\n", spx, spy);
		/*
		if (ds->dimensionX >= ds->maxX) {
			startX = -1;
			spx = 0;
		}
		if (ds->dimensionY >= ds->maxY) {
			startY = -1;
			spy = 0;
		}
		*/
		//printf("initializing frame size of %i buffer of %i\n", ds->dimensionX, ds->buffX);
		for (int y = 0; y < ds->dimensionY; y++) {
			for (int x = 0; x < ds->dimensionX; x++) {
		//for (int y = -ds->buffY/2; y < ds->dimensionY + ds->buffY/2; y++) {
			//for (int x = -ds->buffX/2; x < ds->dimensionX + ds->buffX/2; x++) {
				(ds->data)[index++]	= startX + (xs * x);
				(ds->data)[index++]	= startY + (ys * y);
				for (int i = 0; i < ds->stride-2; i++) {
					(ds->data)[index++] = 1;	
				}

			}
		}
		/*
		for (int y = -ds->dimensionY; y < ds->dimensionY; y+=2) {//screenPortion) { 
			for (int x = -ds->dimensionX; x < ds->dimensionX; x+=2) {//screenPortion) {
				(ds->data)[index++]	= (sizeX/2) + (((float)x / ds->dimensionX) * ds->ratioX);
				(ds->data)[index++]	= (sizeY/2) + (((float)y / ds->dimensionY) * ds->ratioY);
				for (int i = 0; i < ds->stride-2; i++) {
					(ds->data)[index++] = 1;	
				}
			}
		}
	*/
	}
}

void setScreenVBO(DrawScreen *ds) {
	glEnableVertexAttribArray(ds->location);
	glBindBuffer(GL_ARRAY_BUFFER, ds->vbo);
	glVertexAttribPointer(ds->location, ds->stride, GL_FLOAT, GL_FALSE, ds->stride * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(ds->location,1);
}


void resizeTileSet(TileSet *t, int newSizeX, int newSizeY, bool bufferX, bool bufferY) {
	//printf("resizing tile set %i\n", bufferX);
	sizeDrawScreen(t->trans, newSizeX, newSizeY, false, bufferX, bufferY);
	sizeDrawScreen(t->rot, newSizeX, newSizeY, true, bufferX, bufferY);
	sizeDrawScreen(t->color, newSizeX, newSizeY, true, bufferX, bufferY);
	sizeDrawScreen(t->texture, newSizeX, newSizeY, true, bufferX, bufferY);
}

void setTileSize(TileSet *t, float sizeX, float sizeY) {
	t->trans->sizeX = sizeX;
	t->trans->sizeY = sizeY;
	t->rot->sizeX = sizeX;
	t->rot->sizeY = sizeY;
	t->color->sizeX = sizeX;
	t->color->sizeY = sizeY;
	t->texture->sizeX = sizeX;
	t->texture->sizeY = sizeY;
}

//edits final piece of data at moment
//because the x and y shouldn't change unless its a rotation screen, in which all 4 values change
//POS -  mod 1: edits visible
//TEX - mod 2- X val mod 1 - Y val
//ROT - mod 4 - 1 - x y z w
void editData(DrawScreen *ds, int x, int y, float val, int mod) {
	ds->data[((y) * (ds->dimensionX) * ds->stride) + (ds->stride-mod) + (x * ds->stride)] = val;
}

float getData(DrawScreen *ds, int x, int y, int mod) {
	int index = (y * (ds->dimensionX) * ds->stride) + (ds->stride-mod) + (x * ds->stride); 
	if (index >= 0 && index < (ds->dimensionX) * (ds->dimensionY) * ds->stride) {
		return ds->data[index];
	} else {
		return -190;
	}
}

int *getXY(DrawScreen *ds, int index) {
	int y = index / ((ds->dimensionX) * ds->stride);
	int x = (index - (y * (ds->dimensionX) * ds->stride)) / ds->stride;
	//printf("index %i Produced %i, %i\n", index, x, y);
	int *pair = (int*)calloc(sizeof(int), 2);
	pair[0] = x;
	pair[1] = y;
	return pair;
}

void bindData(DrawScreen *ds) {
	glBindBuffer(GL_ARRAY_BUFFER, ds->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ((ds->dimensionX) * (ds->dimensionY) * ds->stride), &((ds->data)[0]), GL_STATIC_DRAW);
}

void clearData(DrawScreen *ds, bool base) {
	int index = 0;
	for (int y = -ds->dimensionY; y < ds->dimensionY; y+=2) { 
		for (int x = -ds->dimensionX; x < ds->dimensionX; x+=2) {
			if (!base) {
				index+=2;
				for (int i = 0; i < ds->stride-2; i++) {
					ds->data[index++] = 0;	
				}
			} else {
				for (int i = 0; i < ds->stride; i++) {
					ds->data[index++] = 0;	
				}
			}
		}
	}
	bindData(ds);
}

void setRots(DrawScreen *ds, float rad) {
	int index = 0;
	for (int y = -ds->dimensionY; y < ds->dimensionY; y+=2) { 
		for (int x = -ds->dimensionX; x < ds->dimensionX; x+=2) {
			ds->data[index++] = cos(rad);	
			ds->data[index++] = -sin(rad);	
			ds->data[index++] = sin(rad);	
			ds->data[index++] = cos(rad);	
		}
	}
	bindData(ds);
}

void setData(DrawScreen *ds, float value) {
	int index = 0;
	for (int y = -ds->dimensionY; y < ds->dimensionY; y+=2) { 
		for (int x = -ds->dimensionX; x < ds->dimensionX; x+=2) {
			ds->data[index++] = value;	
			ds->data[index++] = value;	
			ds->data[index++] = value;	
			ds->data[index++] = value;	
		}
	}
	bindData(ds);
}

void setRot(DrawScreen *ds, int x, int y, float rad) {
	editData(ds, x, y, cos(rad), 4);
	editData(ds, x, y, -sin(rad), 3);
	editData(ds, x, y, sin(rad), 2);
	editData(ds, x, y, cos(rad), 1);	
}

float dirToRad(int d) {
	if (d == 0) {
		return 0;
	} else if (d == 1) {
		return 1.5708;
	} else if (d == 2) {
		return 3.14159;
	} else if (d == 3) {
		return 4.71239;
	}
}

GLuint getTileVAO() {
	return tileVAO;
}

void printData(DrawScreen *ds) {
	for (int y = ds->dimensionY-1; y >= 0; y--) {
		for (int x = 0; x < ds->dimensionX; x++) {
			if (getData(ds, x, y, 2) == 1) {
				printf(" 1 ");
			} else {
				printf(" 0 ");
			}
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void setTileSetID(TileSet *ts, int id) {
	ts->typeID = id;
}
