#ifndef DRAWWORLD
#define DRAWWORLD
typedef struct AnimOrder {
	int order;
	linkedList *anims;
	linkedList *poses;
} AnimOrder;


void drawWorld(World *w, Camera *cam);
void tileCell(TileSet *t, float remainder, int x, int y);
AnimOrder *makeAnimOrder(int order);
void addFormToAnim(AnimOrder *ao, Form *f, Anim *anim, float x, float y);
void drawAnimOrder(AnimOrder *ao, float *sMatrix, float xSize, float ySize);
void freeAnimOrder(AnimOrder *ao);
void drawWorldDebug(World *w, Camera *cam, int tMat, int sMat,int rMat, int color, GLuint squa);
#endif
