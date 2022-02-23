#include "Camera.h"
Camera *defaultCam;

Camera *makeCamera() {
	Camera *c = (Camera *)calloc(sizeof(Camera), 1);
	c->centerX = 0;
	c->centerY = 0;
	c->frameX = 0;
	c->frameY = 0;
	c->defaultFrameX = 0;
	c->defaultFrameY = 0;
}

void initCamera(int x, int y) {
	defaultCam = makeCamera();
	defaultCam->defaultFrameX = defaultCam->frameX = x;	
	defaultCam->defaultFrameY = defaultCam->frameY = y;	
	printf("camera initialized %i, %i\n", defaultCam->frameX, defaultCam->frameY);
}

Camera *getDefaultCam() {
	return defaultCam;
}

void setCenter(Camera *c, float cp[2]) {
	c->centerX = cp[0];
	c->centerY = cp[1];
}

void setFrame(Camera *c, int x, int y) {
	c->frameX = x;
	c->frameY = y;
}


