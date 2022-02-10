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
// if num is zero textue will be processed as individual image which will be split into color layers
// white gen stops texture from flipping the sprites to use them
//   this is because when we generate sprites we flip them 
//		so that the color order doesn't change between usages
textureSource *getTexture(char **name, int num, bool whiteGen) {
	textureSource *ts = findTexture(*name);//textures always saved as first file
	if (ts == NULL) {
		printf("making new texture\n");
		ts = makeTextureFromImages(name, num, whiteGen);
	} else {
		printf("no need to make new texture\n");
	}
	return ts;
}

//will make a singlesprite to a single texture
// if single is false, will dynamically create white layered sprite w/color pallete
textureSource *makeTexture(char *img, bool single) {
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
		ts->name = (char *)calloc(sizeof(char), strlen(img)+1);
		strcpy(ts->name, img);
		if (!single) {
			getImgColors(ts, data, 0, false);
		} else {
			printf("single sprite being made to texture\n");
			unsigned int tex = genTexture(data, ts->width, ts->height);
			ts->tex = (unsigned int*)calloc(sizeof(unsigned int), 1);
			*(ts->tex) = tex;
			ts->numTex = 1;
			ts->colors = (float*)calloc(sizeof(float), 4);
			for (int i = 0; i < 4; i++) {
				(ts->colors)[i] = 1;
			}
		}
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

textureSource *makeTextureFromImages(char **imgs, int num, bool whiteGen) {
	if (num == 1) {
		return makeTexture(*imgs, true);
	} else if (num == 0) {
		return makeTexture(*imgs, false);
	}
	textureSource *ts = (textureSource*)calloc(sizeof(textureSource), 1);
	if (!whiteGen) {
		stbi_set_flip_vertically_on_load(true);
	}
	ts->name = (char *)calloc(sizeof(char), strlen(imgs[0])+1);
	strcpy(ts->name, imgs[0]);
	ts->numTex = num;
	ts->tex = (unsigned int*)calloc(sizeof(unsigned int), num);
	ts->colors = (float*)calloc(sizeof(float), num * 4);
	for (int i = 0; i < num; i++) {
		for (int j =0; j < 4; j++) {
			(ts->colors)[i*4 + j] = 1;
		}
		unsigned char *data = stbi_load(imgs[i], &(ts->width), &(ts->height), &(ts->channels), 0);
		if (data) {
			unsigned int tex = genTexture(data, ts->width, ts->height);
			(ts->tex)[i] = tex;
			stbi_image_free(data);
		} else {
			printf("%s does not exist, texture creation failed\n", imgs[i]);
			freeTextureSource(ts);
			stbi_image_free(data);
			return 0;
		}
	}
	addTexture(ts);
	return ts;
}

int countColors(textureSource *ts, unsigned char *data) {
	linkedList *colors = makeList();
	int numColors = 0;
	for (int i = 0; i < ts->height * ts->width * ts->channels; i+=ts->channels) {
		if (data[i+3] != 0) {
			unsigned char *color = (unsigned char*)calloc(sizeof(unsigned char),4);
			color[0] = data[i];
			color[1] = data[i+1];
			color[2] = data[i+2];
			color[3] = data[i+3];
			if (checkList(&colors, color, compareColor) == true) {
				free(color);
			} else {
				addToList(&colors, color);
				numColors++;
			}
		}
	}
	freeList(&colors);
	return numColors;
}

/* 
 * takes in PNG and converts each color to a separate file and colors them white
 * 	allows for dynamic paletting of sprites
 * ts - textureSource tp be filled in
 * data - raw data of png file
 * numColors - if you know how many colors there are you can save some time by including it
 *	otherwise <=0 will count the colors in the fle for you
 * writeToFile - if true will also write textures to file
 */
void getImgColors(textureSource *ts, unsigned char *data, int numColors, bool writeToFile) {
	if (numColors <= 0) {
		numColors = countColors(ts, data);
	}
	linkedList *colors = makeList();
	int dataLength = ts->height * ts->width * ts->channels;
	colorLayer *layers = (colorLayer*)calloc(sizeof(colorLayer), numColors);
	for (int i = 0; i < numColors; i++) {
		layers[i].data = (unsigned char*)calloc(sizeof(unsigned char), dataLength);
	}
	ts->colors = (float*)calloc(sizeof(float), numColors * 4);
	int colorSeen = 0;
	unsigned char *color;
	for (int i = 0; i < dataLength; i+=ts->channels) {
		if (data[i+3] != 0) {
			color = (unsigned char*)calloc(sizeof(unsigned char),4);
			color[0] = data[i];
			color[1] = data[i+1];
			color[2] = data[i+2];
			color[3] = data[i+3];
			if (checkList(&colors, color, compareColor) == false) {
				//we havent seen this color
				//process it by assigning it an empty color layer
				addToList(&colors, color);
				for (int j = 0; j < 4; j++) {
					//int step = (numColors * 3) - ((colorSeen+1) * 3);
					int step = colorSeen * 4;
					//layers[numColors-1-colorSeen].color[j] = color[j];
					layers[colorSeen].color[j] = color[j];
					(ts->colors)[step + j] = (float)color[j]/255;
				}
				//set any color on layer to pure white and solid, so palette can be applied purely
				for (int j = 0; j < 4; j++) {
					layers[colorSeen].data[i+j] = 255;
				}
				colorSeen++;
			} else {
				for (int j = 0; j < numColors; j++) {
					if (compareColor(layers[j].color, color)) {
						//printf("found color-%u,%u,%u at %i\n",color[0], color[1], color[2], j);
						for (int k = 0; k < 4; k++) {
							layers[j].data[i+k] = 255;
						}
						break;
					}
				}
				free(color);
			}
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
	if (writeToFile) {
		writeTextureToFile(ts, layers);
	}
	freeList(&colors);
	for (int i = 0; i < numColors; i++) {
		free(layers[i].data);
	}
	free(layers);
}

void freeTextureSource(textureSource* ts) {
	free(ts->name);
	free(ts->tex);
	free(ts->colors);
	free(ts);
}


void writeTextureToFile(textureSource *ts, colorLayer *layers) {
	int sLen = strlen(ts->name);
	char *fName = (char*)calloc(sizeof(char), sLen + 2);
	strncpy(fName, ts->name, sLen - 4);
	for (int i = 0; i < ts->numTex; i++) {
		fName[sLen - 4] = (unsigned char)i + 48;
		stbi_write_png(fName, ts->width, ts->height, ts->channels, layers[i].data, ts->width * ts->channels);	
	}
	free(fName);
}
