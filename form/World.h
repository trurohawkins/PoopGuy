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
Form *takeForm(int x, int y);
Form *removeForm(Form *f);
void dirtFloor(int height);
void makeSquare(int x, int y, int z);
void makeCircle(int x, int y, int r);
