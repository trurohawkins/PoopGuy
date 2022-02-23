#include "Tile.h"

float *translations;
int dim;
linkedList *TileSets;
int tileCount = 0;

void initTileSets() {
	TileSets = makeList();
}

TileSet *makeTileSet(Anim *a, int frame, int world) {
	TileSet *ts = (TileSet*)calloc(sizeof(TileSet), 1);
	ts->set = a;
	ts->typeID = -1;
	GLuint tileShader = getSP(2);
	glUseProgram(tileShader);
	printf("making tileset frame:%i world%i\n", frame, world);
	ts->color = makeDrawScreen(frame, world, 1, 4, true);
	ts->trans = makeDrawScreen(frame, world, 3, 3, false);
	ts->rot = makeDrawScreen(frame, world, 4, 4, true);
	ts->texture = makeDrawScreen(frame, world, 5, 2, true);
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

DrawScreen *makeDrawScreen(int dimension, int maxDimension, int location, int stride, bool base) {
	DrawScreen *ds = (DrawScreen*)calloc(sizeof(DrawScreen), 1);
	ds->dimension = dimension;// + 1;
	ds->max = maxDimension;
	ds->data = (float*)calloc(sizeof(float), maxDimension * maxDimension * stride);
	ds->stride = stride;
	initializeData(ds, base);
	glGenBuffers(1, &(ds->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, ds->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (dimension * dimension * stride), &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	ds->location = location;
	return ds;
}

void initializeData(DrawScreen *ds, bool base) {
	int index = 0;
	if (base) {
		float size = 2.0/ds->dimension;
		for (int y = -ds->dimension; y < ds->dimension; y+=2) { 
			for (int x = -ds->dimension; x < ds->dimension; x+=2) {
					(ds->data)[index++] = 1;	
			}
		}
	} else {
		float size = 2.0/ds->dimension;
		for (int y = -ds->dimension; y < ds->dimension; y+=2) { 
			for (int x = -ds->dimension; x < ds->dimension; x+=2) {
				(ds->data)[index++]	= (size/2) + ((float)x / ds->dimension);
				(ds->data)[index++]	= (size/2) + ((float)y / ds->dimension);
				for (int i = 0; i < ds->stride-2; i++) {
					(ds->data)[index++] = 1;	
				}
			}
		}
	}
}

void setScreenVBO(DrawScreen *ds) {
	glEnableVertexAttribArray(ds->location);
	glBindBuffer(GL_ARRAY_BUFFER, ds->vbo);
	glVertexAttribPointer(ds->location, ds->stride, GL_FLOAT, GL_FALSE, ds->stride * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(ds->location,1);
}

void resizeDrawScreen(DrawScreen *ds, int newSize, bool base) {
	if (newSize > 0 && newSize <= ds->max) {
		ds->dimension = newSize;
		initializeData(ds, base);
		glGenBuffers(1, &(ds->vbo));
		glBindBuffer(GL_ARRAY_BUFFER, ds->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (ds->dimension * ds->dimension * ds->stride), &((ds->data)[0]), GL_STATIC_DRAW);
		setScreenVBO(ds);
	}

}

void resizeTileSet(TileSet *t, int newSize) {
	if (newSize > 0 && newSize <= t->trans->max) {
		resizeDrawScreen(t->trans, newSize, false);
		resizeDrawScreen(t->rot, newSize, true);
		resizeDrawScreen(t->color, newSize, true);
		resizeDrawScreen(t->texture, newSize, true);
	}
}

//edits final piece of data at moment
//because the x and y shouldn't change unless its a rotation screen, in which all 4 values change
//POS -  mod 1: edits visible
//TEX - mod 2- X val mod 1 - Y val
//ROT - mod 4 - 1 - x y z w
void editData(DrawScreen *ds, int x, int y, float val, int mod) {
	ds->data[(y * ds->dimension * ds->stride) + (ds->stride-mod) + (x * ds->stride)] = val;
}

float getData(DrawScreen *ds, int x, int y, int mod) {
	int index = (y * ds->dimension * ds->stride) + (ds->stride-mod) + (x * ds->stride); 
	if (index >= 0 && index < ds->dimension * ds->dimension * ds->stride) {
		return ds->data[index];
	} else {
		return -190;
	}
}

int *getXY(DrawScreen *ds, int index) {
	int y = index / (ds->dimension * ds->stride);
	int x = (index - (y * ds->dimension * ds->stride)) / ds->stride;
	//printf("index %i Produced %i, %i\n", index, x, y);
	int *pair = (int*)calloc(sizeof(int), 2);
	pair[0] = x;
	pair[1] = y;
	return pair;
}

void bindData(DrawScreen *ds) {
	glBindBuffer(GL_ARRAY_BUFFER, ds->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (ds->dimension * ds->dimension * ds->stride), &((ds->data)[0]), GL_STATIC_DRAW);
}

void clearData(DrawScreen *ds, bool base) {
	int index = 0;
	for (int y = -ds->dimension; y < ds->dimension; y+=2) { 
		for (int x = -ds->dimension; x < ds->dimension; x+=2) {
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
	for (int y = -ds->dimension; y < ds->dimension; y+=2) { 
		for (int x = -ds->dimension; x < ds->dimension; x+=2) {
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
	for (int y = -ds->dimension; y < ds->dimension; y+=2) { 
		for (int x = -ds->dimension; x < ds->dimension; x+=2) {
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

void printData(DrawScreen *ds) {
	for (int y = ds->dimension-1; y >= 0; y--) {
		for (int x = 0; x < ds->dimension; x++) {
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
