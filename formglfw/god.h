#ifndef GODPLAYER
#define GODPLAYER

typedef struct GOD {
	Player *p;
	short *move;
	bool *zoom;
	float *pos;
	int *frame;
	float speed;
	int zoomSpeedX;
	int zoomSpeedY;
	World *world;
	Camera *cam;
} GOD;

GOD *makeGodPlayer(float x, float y, int fx, int fy);
void freeGod(void*);
void zoomOut(void *v, float f);
void zoomIn(void *v, float f);
void camUp(void *, float);
void camLeft(void *, float);
void camDown(void *, float);
void camRight(void *, float);
void moveGodView(Form *v, Action *a);
void godOff(GOD *god);
void godOn(GOD *g);
void godSetFrame(GOD* g);
void setGod(GOD *g, float px, float py, int fx, int fy);
#endif
