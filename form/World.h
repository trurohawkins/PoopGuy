typedef struct World
{
	Form ***map; 
	int x;
	int y;
	// world state?;
} World;

void makeWorld(int x, int y);
void deleteWorld();
void placeForm(int x, int y, Form *form);
Form *removeForm(int x, int y);
