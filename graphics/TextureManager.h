#ifndef TEXMAN
#define TEXMAN
typedef struct textureSource {
	char *name;
	unsigned int tex;
	int width;
	int height;
	int channels;
} textureSource;

void makeTextureManager();
void addTexture(textureSource *ts);
void deleteTextureManager();
textureSource *makeTexture(char *img);
textureSource *findTexture(char *img);
textureSource *getTexture(char *name);
void freeTextureSource(textureSource *ts);
#endif
