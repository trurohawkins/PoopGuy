typedef struct World
{
	Form **map; 
	int x;
	int y;
	// world state?;
} World;

World *makeWorld(int x, int y);
void deleteWorld(World *world);
void placeForm(World *world, int x, int y, Form *form);
