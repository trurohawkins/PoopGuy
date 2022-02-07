#ifndef TEXMAN
#define TEXMAN

typedef struct textureSource {
	char *name;
	unsigned int *tex;
	float *colors;
	int numTex;
	int width;
	int height;
	int channels;
} textureSource;

typedef struct colorLayer {
	unsigned char color[3];
	unsigned char* data;
} colorLayer;

void makeTextureManager();
void addTexture(textureSource *ts);
void deleteTextureManager();
unsigned int genTexture(unsigned char *data, int wid, int hei);
textureSource *makeTexture(char *img);
colorLayer *getImgColors(textureSource *ts, unsigned char *data);
textureSource *findTexture(char *img);
textureSource *getTexture(char *name);
void freeTextureSource(textureSource *ts);
//void loadPalette(textureSource *ts, float *palette);
#endif
