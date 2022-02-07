#include "TextureManager.h"
linkedList *textureManager;

void makeTextureManager() {
	textureManager = makeList();
}

void addTexture(textureSource *ts) {
	addToList(&textureManager, ts);
}

void deleteTextureManager() {
	linkedList *cur = textureManager;
	while (cur != NULL) {
		linkedList *next = cur->next;
		if (cur->data != NULL) {
			freeTextureSource((textureSource*)(cur->data));
		}
		free(cur);
		cur = next;
	}
}

unsigned int genTexture(unsigned char *data, int wid, int hei) {
	unsigned int tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wid, hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	return tex;
}

textureSource *makeTexture(char *img) {
	textureSource *ts = (textureSource*)calloc(sizeof(textureSource), 1);
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(img, &(ts->width), &(ts->height), &(ts->channels), 0);
	if (data) {
		/*
		unsigned int tex = genTexture(data, ts->width, ts->height);
		ts->tex = (unsigned int*)calloc(sizeof(unsigned int), 1);
		*(ts->tex) = tex;
		ts->numTex = 1;
		*/
		getImgColors(ts, data);
		ts->name = (char *)calloc(sizeof(char), strlen(img)+1);
		strcpy(ts->name, img);
		addTexture(ts);
		printf("number of textures %i\n", ts->numTex);
	} else {
		free(ts);
		printf("failed to load texture from file %s\n", img);
		ts = 0;
	}
	stbi_image_free(data);
	return ts;
}

colorLayer *getImgColors(textureSource *ts, unsigned char *data) {
	linkedList *colors = makeList();
	int dataLength = ts->height * ts->width * ts->channels;
	int numColors = 0;
	for (int i = 0; i < dataLength; i+=ts->channels) {
		if (data[i+3] != 0) {
			unsigned char *color = (unsigned char*)calloc(sizeof(unsigned char),3);
			color[0] = data[i];
			color[1] = data[i+1];
			color[2] = data[i+2];
			if (checkList(&colors, color, compareColor) == true) {
				free(color);
			} else {
				addToList(&colors, color);
				//unsigned char *layer = (unsigned char *)calloc(sizeof(unsigned char), dataLength);
				numColors++;
			}
		}
	}
	freeList(&colors);
	colors = makeList();
	colorLayer *layers = (colorLayer*)calloc(sizeof(colorLayer), numColors);
	for (int i = 0; i < numColors; i++) {
		layers[i].data = (unsigned char*)calloc(sizeof(unsigned char), dataLength);
	}
	ts->colors = (float*)calloc(sizeof(float), numColors * 3);
	int colorSeen = 0;
	unsigned char *color;
	for (int i = 0; i < dataLength; i+=ts->channels) {
		if (data[i+3] != 0) {
			color = (unsigned char*)calloc(sizeof(unsigned char),3);
			color[0] = data[i];
			color[1] = data[i+1];
			color[2] = data[i+2];
			if (checkList(&colors, color, compareColor) == false) {
				addToList(&colors, color);
				for (int j = 0; j < 3; j++) {
					int step = colorSeen * 3;
					layers[colorSeen].color[j] = color[j];
					(ts->colors)[step + j] = (float)color[j]/255;
					//printf("%i - got color %u from data, saved as %f\n", colorSeen, color[j], (ts->colors)[colorSeen + j]);
				}
				//layers[colorSeen].color[1] = color[1];
				//layers[colorSeen].color[2] = color[2];
				layers[colorSeen].data[i] = 255;
				layers[colorSeen].data[i+1] = 255;
				layers[colorSeen].data[i+2] = 255;
				layers[colorSeen].data[i+3] = 255;
				colorSeen++;
			} else {
				for (int j = 0; j < numColors; j++) {
					if (compareColor(layers[j].color, color)) {
						//printf("found color-%u,%u,%u at %i\n",color[0], color[1], color[2], j);

						layers[j].data[i] = 255;
						layers[j].data[i+1] = 255;
						layers[j].data[i+2] = 255;
						layers[j].data[i+3] = 255;
						j = numColors + 1;
					}
				}
				free(color);
			}
			//free(color);
		}
	}
	/*
	for (int i = 0; i < numColors*3; i++) {
		printf(" %i ",(ts->colors)[i]); 
	}
	printf("\n");
	*/
	ts->tex = (unsigned int*)calloc(sizeof(unsigned int), numColors);
	for (int i = 0; i < numColors; i++) {
		unsigned int tex = genTexture(layers[i].data, ts->width, ts->height);
		(ts->tex)[i] = tex;
	}
	ts->numTex = numColors;
/*	
	printf("data -\n");
	for (int i = 0; i < dataLength; i++) {
		for (int j = 0; j < 4; j++, i++) {
			printf(" %u ", layers[0].data[i]);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < numColors; i++) {
		char *fName = (char*)calloc(sizeof(char), 9);
		strcat(fName,"col .png");
		fName[3] = (unsigned char)i + 48;
		stbi_write_png(fName, ts->width, ts->height, ts->channels, layers[i].data, ts->width * ts->channels);	
		free(fName);
	}
	*/
	freeList(&colors);
	for (int i = 0; i < numColors; i++) {
		free(layers[i].data);
	}
	free(layers);
	return &(layers[0]);
}

void freeTextureSource(textureSource* ts) {
	free(ts->name);
	free(ts->tex);
	free(ts->colors);
	free(ts);
}

textureSource *findTexture(char *name) {
	linkedList *cur = textureManager;
	while (cur != NULL) {
		textureSource *tmp = (textureSource*)cur->data;
		if (tmp != NULL) {
			//printf("checking cur: %s
			if (strcmp(name, tmp->name) == 0) {
				return tmp;
			}
		}
		cur = cur->next;
	}
	return NULL;
}

textureSource *getTexture(char *name) {
	textureSource *ts = findTexture(name);
	if (ts == NULL) {
		printf("making new texture\n");
		ts = makeTexture(name);
	} else {
		printf("no need to make new texture\n");
	}
	return ts;
}

