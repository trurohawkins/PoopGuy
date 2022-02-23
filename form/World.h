#ifndef WORLD
#define WORLD
typedef struct World
{
	Cell ***map; 
	int x;
	int y;
	linkedList *terrain;
	// world state?;
} World;
#include "procGen.h"
#include "../actor/Eco.h"

void makeWorld(int x, int y);
World *getWorld();
void deleteWorld();
void deleteTerrain();
void placeForm(int x, int y, Form *form);
int getFormID(int x, int y);
Form *checkForm(int x, int y);
Form *takeForm(int x, int y);
Form *removeForm(Form *f);
void freeWorld();
Form *makeDirt(float);
Form *makeStone();
void dirtFloor(int height);
void makeSquare(int x, int y, int z);
void makeStoneSquare(int x, int y, int z);
void makeCircle(int x, int y, int r);
#endif
