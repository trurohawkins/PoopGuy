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
	unsigned char color[4];
	unsigned char* data;
} colorLayer;

void makeTextureManager();
void addTexture(textureSource *ts);
void deleteTextureManager();
unsigned int genTexture(unsigned char *data, int wid, int hei);
textureSource *makeTexture(char *img, bool single);
textureSource *makeTextureFromImages(char **imgs, int num, bool whiteGen);
int countColors(textureSource *ts, unsigned char* data);
void getImgColors(textureSource *ts, unsigned char *data, int numColors, bool writeToFile);
textureSource *findTexture(char *img);
textureSource *getTexture(char **name, int num, bool whiteGen);
void freeTextureSource(textureSource *ts);
void writeTextureToFile(textureSource *ts, colorLayer *layers);
#endif
