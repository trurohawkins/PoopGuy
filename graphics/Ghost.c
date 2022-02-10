linkedList *BG;
linkedList *FG;

void initBackgroundGhosts(){
	BG = makeList();
}

void addBackground(Ghost *gho) {
	addToList(&BG, gho);
}
void drawBG(float *sMatrix, GLuint sScale, GLuint sTrans, GLuint sRot, GLuint texColor) {
	drawGround(BG, sMatrix, sScale, sTrans, sRot, texColor);
}

void freeBG() {
	freeList(&BG);
}
void initForegroundGhosts() {
	FG = makeList();
}

void addForeground(Ghost *gho) {
	addToList(&FG, gho);
}

void drawFG(float *sMatrix, GLuint sScale, GLuint sTrans, GLuint sRot, GLuint texColor) {
	drawGround(FG, sMatrix, sScale, sTrans, sRot, texColor);
}

void freeFG() {
	freeList(&FG);
}

void drawGround(linkedList *ground, float *sMatrix,  GLuint sScale, GLuint sTrans, GLuint sRot, GLuint texColor) {
	linkedList *cur = ground;
	while (cur != NULL) {
		if (cur->data != NULL) {
			Ghost *gho = (Ghost*)cur->data;
			drawGhost(gho, sMatrix, sScale, sTrans, sRot, texColor);
		}
		cur = cur->next;
	}
}

Ghost *makeGhost(char *baseFile, int numColors, int rows, int cols, GLuint tc, GLuint ts) {
	printf("ghost being made\n");
	bool generated = false;
	char **sprites = (char**)calloc(sizeof(char*), numColors);
	int sLen = strlen(baseFile);
	if (numColors > 1) {
		generated = true;
		for (int i = 0; i < numColors; i++) {
			sprites[i] = (char*)calloc(sizeof(char), sLen + 2);
			sprites[i][sLen-4] = (unsigned char)i + 48;
			strncpy(sprites[i], baseFile, sLen - 4);
			strcat(sprites[i], ".png");
		}
	} else {
		*sprites = (char*)calloc(sizeof(char), sLen + 1);
		strcpy(*sprites, baseFile); 
	}
	Anim *poo = makeAnim(sprites, numColors, generated, rows, cols, tc, ts);
	/*
	if (numColors != 1) {
		setPalette(pNum, poo);
	}
	*/
	for (int i = 0; i < numColors; i++) {
		free(sprites[i]);
	}
	free(sprites);
	GLuint spriteVao = makeSpriteVao(1, 1);
	animAddVao(poo, spriteVao);//makeSpriteVao(1, 1));
	addAnim(poo);
	Ghost *gho = (Ghost *)calloc(sizeof(Ghost), 1);
	gho->xp = -0.01;
	gho->yp = 0;
	gho->xSize = 1;
	gho->ySize = 1;
	gho->roto = 3;
	gho->xInvert = false;
	gho->yInvert = false;
	gho->a = poo;
	return gho;
}

void drawGhost(Ghost *gho, float *sMatrix, GLuint sScale, GLuint sTrans, GLuint sRot, GLuint texColor) {
	Anim *a = gho->a;
	sMatrix[3] = 0;
	sMatrix[7] = 0;
	sMatrix[0] = gho->xSize * a->scale[0] * convertInvert(gho->xInvert);//a->flip[0];
	sMatrix[5] = gho->ySize * a->scale[1] * convertInvert(gho->yInvert);//a->flip[1];
	glUniformMatrix4fv(sScale, 1, GL_TRUE, sMatrix);
	setSpriteTexture(a);
	sMatrix[3] = (-1 + gho->xSize/2) + (gho->xp * gho->xSize);// + -a->flip[0] * 0.01f;
	sMatrix[7] = (-1 + gho->ySize/2) + (gho->yp * gho->ySize);// + 0.01f;	
	sMatrix[0] = 1;//xSize * a->scale[0] * a->flip[0];
	sMatrix[5] = 1;//ySize * a->scale[1] * a->flip[1];
	glUniformMatrix4fv(sTrans, 1, GL_TRUE, sMatrix);
	float rad = rotoToRadian(gho->roto);
	float rMatrix[] = {
		cos(rad), -sin(rad), 0.0, 0.0,
		sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0 ,0.0,
		0.0, 0.0, 0.0, 1.0
	};
	glUniformMatrix4fv(sRot, 1, GL_TRUE, rMatrix);
	drawSprite(a, texColor);
}


void moveGhost(Ghost *gho, int xd, int yd, float xPow, float yPow) {
	if (gho != NULL) {
		gho->xp += xd * xPow;
		gho->yp += yd * yPow;
	}
}

void freeGhost(Ghost *gho) {
	free(gho);
}

