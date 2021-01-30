typedef struct World
{
	Form ***map; 
	int x;
	int y;
	linkedList *terrain;
	// world state?;
} World;

void makeWorld(int x, int y);
void deleteWorld();
void deleteTerrain();
void placeForm(int x, int y, Form *form);
Form *removeForm(int x, int y);
void dirtFloor(int height);
void makeSquare(int x, int y, int z);
