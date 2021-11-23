#ifndef WORLD
#define WORLD
typedef struct World
{
	Form ***map; 
	int x;
	int y;
	linkedList *terrain;
	// world state?;
} World;
#include "procGen.h"

void makeWorld(int x, int y);
World *getWorld();
void deleteWorld();
void deleteTerrain();
void placeForm(int x, int y, Form *form);
Form *takeForm(int x, int y);
Form *removeForm(Form *f);
Form *makeDirt();
void dirtFloor(int height);
void makeSquare(int x, int y, int z);
void makeCircle(int x, int y, int r);
#endif
