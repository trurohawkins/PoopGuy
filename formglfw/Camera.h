#ifndef CAMERA
#define CAMERA
typedef struct Camera {
	int frameX;
	int frameY;
	int centerX;
	int centerY;
	int defaultFrameX;
	int defaultFrameY;
} Camera;

Camera *makeCamera();
void initCamera(int x, int y);
Camera *getDefaultCam();
void setCenter(Camera *c, float cp[2]);
void setFrame(Camera *c, int x, int y);
#endif
