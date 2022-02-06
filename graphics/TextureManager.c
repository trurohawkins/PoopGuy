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

textureSource *makeTexture(char *img) {
	textureSource *ts = (textureSource*)calloc(sizeof(textureSource), 1);
	glGenTextures(1, &(ts->tex));
	glBindTexture(GL_TEXTURE_2D, (ts->tex));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	//int ts->width, ts->height, ts=>channels;
	unsigned char *data = stbi_load(img, &(ts->width), &(ts->height), &(ts->channels), 0);
	/*
	for (int i = 0; i < ts->height; i++) {
		for (int j = 0; j < ts->width * ts->channels; j++) {
			printf("%u ", data[(i*ts->width)+ j]);	
		}
	}
	*/
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ts->width, ts->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		ts->name = (char *)calloc(sizeof(char), strlen(img)+1);
		strcpy(ts->name, img);
		addTexture(ts);
	} else {
		free(ts);
		printf("failed to load texture from file %s\n", img);
		ts = 0;
	}
	stbi_image_free(data);
	return ts;
}

void freeTextureSource(textureSource* ts) {
	free(ts->name);
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
