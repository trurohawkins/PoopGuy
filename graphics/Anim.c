#include "Anim.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
 /*
	GLuint tc, ts: tc = uniform locations for matrices that determine where in the sprite sheet we are drawing from
*/
#include "AnimList.c"
#include "TextureManager.c"

Anim *makeAnim(char *sheet, int rows, int col, GLuint tc, GLuint ts) { 
	Anim *a = (Anim*)calloc(sizeof(Anim), 1);
	/*
	unsigned int tex;
//	glGenTextures(1, &(a->texture));
	//glBindTexture(GL_TEXTURE_2D, a->texture);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(sheet, &width, &height, &nrChannels, 0);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width * nrChannels + 1000; j++) {
			printf("%u ", data[(i*width)+ j]);	
		}
	}
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		printf("failed to load texture from file %s\n", sheet);
	}
	stbi_image_free(data);
	a->texture = tex;
	a->frameX = 1.0f/col;
	a->frameY = 1.0f/rows;
	rows-height-y
	cols-width-x
	*/
	a->texture = getTexture(sheet);
	a->frameX = 1.0f/col;
	a->frameY = 1.0f/rows;
	a->frame = 0;
	a->sprite = 0;
	a->speed = 5;
	a->spriteNum = rows;
	a->length = (int*)calloc(sizeof(int), col);
	a->length[0] = 0;
	for (int i = 1; i <  col; i++) {
		a->length[i] = -1;
	}
	a->scale[0] = 1;
	a->scale[1] = 1;
	a->flip[0] = 1;
	a->flip[1] = 1;
	a->roto = 3;
	a->vao = -1;
	a->texCoords = tc;
	a->texScale = ts;
	a->palette = (float*)calloc(sizeof(float), a->texture->numTex * 3);
	for (int i = 0; i < a->texture->numTex * 3; i++) {
		float f = (a->texture->colors)[i];
		(a->palette)[i] = f;
	}
	//a->palette = a->texture->colors;
	return a;
}

float rotoToRadian(int d) {
	if (d == 0) {
		return 1.5708;
	} else if (d == 2) {
		return 4.71239;
	}
	return 0;
}

void freeAnim(Anim *a) {
	free(a->palette);
	free(a->length);
	free(a);
}

void setScale(Anim *a, int x, int y) {
	a->scale[0] = x;
	a->scale[1] = y;
}

void setFlipX(Anim *a, int x) {
	a->flip[0] = x;
}

void setFlipY(Anim *a, int y) {
	a->flip[1] = y;
}

void setRotation(Anim *a, int d) {
	a->roto = d;
}

void addSprite(Anim *a, int index, int len) {
	if (index >= 0 && index < a->spriteNum) {
		a->length[index] = len;
	}
}

void animAddVao(Anim *a, unsigned int vao) {
	a->vao = vao;
}

void animate(Anim *a) {
	//printf("cur sprite: %i\n", a->sprite);
	if (a->length[a->sprite] > 0) {
		if (a->speedCounter > a->speed) {
			a->frame = (a->frame + 1) % a->length[a->sprite];
			a->speedCounter = 0;
		} else {
			a->speedCounter++;
		}
	}
}

void changeSprite(Anim *a, int index) {
	if (index >= 0 && index < a->spriteNum && a->sprite != index) {
		if (a->length[index] != -1) {
			a->sprite = index;
			a->frame = 0;
		}
	}
}

float getCoordX(Anim *a) {
	//printf("%f\n", a->frame * a->frameX);
	return a->frame * a->frameX;
}

float getCoordY(Anim *a) {
	float cy = ((a->spriteNum-1) - a->sprite) * a->frameY + 1;
	return cy;//((a->sprite) * -a->frameY);
}

void setSpriteTexture(Anim *a) {
	float tMat [] = {
		1.0, 0.0, getCoordX(a),
		0.0, 1.0, getCoordY(a),
		0.0, 0.0, 1.0,
	};
	float sMat [] = {
		a->frameX, 0.0, 0.0,
		0.0, a->frameY, 0.0,
		0.0, 0.0, 1.0,
	};
	glUniformMatrix3fv(a->texCoords, 1, GL_TRUE, tMat);
	glUniformMatrix3fv(a->texScale, 1, GL_TRUE, sMat);
}

void drawSprite(Anim *a, GLuint texColor) {
	glUniform2f(a->texCoords, getCoordX(a), getCoordY(a));

	glBindVertexArray(a->vao);
	textureSource *ts = a->texture;
	for (int i = 0; i < ts->numTex; i++) {
		int step = i * 3;
		glUniform3f(texColor,(a->palette)[step],(a->palette)[step+1], (a->palette)[step+2]);
		//printf("layer %i - color: %i, %i, %i\n", i,(ts->colors)[step],(ts->colors)[step+1], (ts->colors)[step+2]);
		//printf("drawing sprite %i\n", (a->texture->tex)[i]);
		glBindTexture(GL_TEXTURE_2D, (a->texture->tex)[i]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void loadPalette(Anim *a, float *palette) {
	for (int i = 0; i < a->texture->numTex; i++) {
		int step = i * 3;
		a->palette[step] = palette[step];
		a->palette[step+1] = palette[step+1];
		a->palette[step+2] = palette[step+2];
	}
}

