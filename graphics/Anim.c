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
#include "UI.c"

GLuint tcTrans;
GLuint tcScale;
GLuint tcColor;

Anim *makeAnim(char **sheet, int spriteNum, bool generated, int rows, int col) { 
	Anim *a = (Anim*)calloc(sizeof(Anim), 1);
	a->drawOrder = 0;
	a->texture = getTexture(sheet, spriteNum, generated);
	if (a->texture == NULL) {
		printf("texture not made well\n");
	}
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
	a->offset[0] = 0;
	a->offset[1] = 0;
	a->roto = 3;
	a->vao = -1;
	a->palette = (float*)calloc(sizeof(float), a->texture->numTex * 4);
	for (int i = 0; i < a->texture->numTex * 4; i++) {
		float f = (a->texture->colors)[i];
		//printf("color %i is %f\n", i, f);
		(a->palette)[i] = f;
	}
	//a->palette = a->texture->colors;
	return a;
}

void getUniformValue(GLuint texShader, char *name, GLuint *dest) {
	GLuint t = glGetUniformLocation(texShader, name);
	if (t == -1) {
		printf("shader doesnt have a var %s\n", name);
	} else {
		*dest = t;
		printf("got value %u for %s\n", t, name);
	}
}

void setTexTrans(GLuint tt) {
	if (tt == -1) {
		printf("frag doesnt have a var tcTrans\n");
	} else {
		tcTrans = tt;
	}
}

void setTexScale(GLuint ts) {
	if (ts == -1) {
		printf("frag doesnt have a var tcScale\n");
	} else {
		tcScale = ts;
	}
}

void setTexColor(GLuint tc) {
	if (tc == -1) {
		printf("frag doesnt have a var colorShift\n");
	} else {
		tcColor = tc;
	}
}

void initTexInts(GLuint texShader) {
	getUniformValue(texShader, "tcScale", &tcScale);
	getUniformValue(texShader, "tcTrans", &tcTrans);
	getUniformValue(texShader, "colorShift", &tcColor);
	glUseProgram(texShader);
	float tscMat [] = {
		//1.0f/6, 0.0, 0.0,
		//0.0, 1.0f/4, 0.0,
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	};
	float ttcMat [] = {
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,//-1.0f/4,
		0.0, 0.0, 1.0,
	};
	glUniformMatrix3fv(tcScale, 1, GL_TRUE, tscMat);
	glUniformMatrix3fv(tcTrans, 1, GL_TRUE, ttcMat);
	glUniform3f(tcColor, 255, 255, 255);
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

void setOffset(Anim *a, float x, float y) {
	a->offset[0] = x;
	a->offset[1] = y;
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

void setDrawOrder(Anim *a, int o) {
	a->drawOrder = o;
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
	/*
	glUniformMatrix3fv(a->texCoords, 1, GL_TRUE, tMat);
	glUniformMatrix3fv(a->texScale, 1, GL_TRUE, sMat);
	*/
	glUniformMatrix3fv(tcTrans, 1, GL_TRUE, tMat);
	glUniformMatrix3fv(tcScale, 1, GL_TRUE, sMat);
}

void drawSprite(Anim *a) {
	glUniform2f(tcTrans, getCoordX(a), getCoordY(a));

	glBindVertexArray(a->vao);
	textureSource *ts = a->texture;
	for (int i = 0; i < ts->numTex; i++) {
		int step = i * 4;
		glUniform4f(tcColor,(a->palette)[step],(a->palette)[step+1], (a->palette)[step+2], (a->palette)[step+3]);
		//printf("layer %i - color: %f, %f, %f, %f\n", i,(a->palette)[step],(a->palette)[step+1], (a->palette)[step+2], (a->palette)[step+3]);
		//printf("drawing sprite %i\n", (a->texture->tex)[i]);
		glBindTexture(GL_TEXTURE_2D, (a->texture->tex)[i]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void loadPalette(Anim *a, float *palette) {
	for (int i = 0; i < a->texture->numTex; i++) {
		int step = i * 4;
		a->palette[step] = palette[step];
		a->palette[step+1] = palette[step+1];
		a->palette[step+2] = palette[step+2];
		a->palette[step+3] = palette[step+3];
	}
}

