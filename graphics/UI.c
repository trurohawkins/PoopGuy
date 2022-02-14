linkedList *BG;
linkedList *FG;

void initBackgroundUI(){
	BG = makeList();
}

void addBackground(UI *ui) {
	addToList(&BG, ui);
}
void drawBG(float *sMatrix, GLuint sScale, GLuint sTrans, GLuint sRot) {
	drawGround(BG, sMatrix, sScale, sTrans, sRot);
}

void freeBG() {
	freeList(&BG);
}
void initForegroundUI() {
	FG = makeList();
}

void addForeground(UI *ui) {
	addToList(&FG, ui);
}

void drawFG(float *sMatrix, GLuint sScale, GLuint sTrans, GLuint sRot) {
	drawGround(FG, sMatrix, sScale, sTrans, sRot);
}

void freeFG() {
	freeList(&FG);
}

void drawGround(linkedList *ground, float *sMatrix,  GLuint sScale, GLuint sTrans, GLuint sRot) {
	linkedList *cur = ground;
	while (cur != NULL) {
		if (cur->data != NULL) {
			UI *ui = (UI*)cur->data;
			drawUI(ui, sMatrix, sScale, sTrans, sRot);
		}
		cur = cur->next;
	}
}

UI *makeUI(char *baseFile, int numColors, int rows, int cols) {
	printf("uist being made %i\n", numColors);
	bool generated = false;
	char **sprites = (char**)calloc(sizeof(char*), max(1, numColors));
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
	Anim *poo = makeAnim(sprites, numColors, generated, rows, cols);
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
	UI *ui = (UI *)calloc(sizeof(UI), 1);
	ui->xp = -0.01;
	ui->yp = 0;
	ui->xSize = 1;
	ui->ySize = 1;
	ui->roto = 3;
	ui->xInvert = false;
	ui->yInvert = false;
	ui->a = poo;
	return ui;
}

void drawUI(UI *ui, float *sMatrix, GLuint sScale, GLuint sTrans, GLuint sRot) {
	Anim *a = ui->a;
	sMatrix[3] = 0;
	sMatrix[7] = 0;
	sMatrix[0] = ui->xSize * a->scale[0] * convertInvert(ui->xInvert);//a->flip[0];
	sMatrix[5] = ui->ySize * a->scale[1] * convertInvert(ui->yInvert);//a->flip[1];
	glUniformMatrix4fv(sScale, 1, GL_TRUE, sMatrix);
	setSpriteTexture(a);
	sMatrix[3] = (-1 + ui->xSize/2) + (ui->xp * ui->xSize);// + -a->flip[0] * 0.01f;
	sMatrix[7] = (-1 + ui->ySize/2) + (ui->yp * ui->ySize);// + 0.01f;	
	sMatrix[0] = 1;//xSize * a->scale[0] * a->flip[0];
	sMatrix[5] = 1;//ySize * a->scale[1] * a->flip[1];
	glUniformMatrix4fv(sTrans, 1, GL_TRUE, sMatrix);
	float rad = rotoToRadian(ui->roto);
	float rMatrix[] = {
		cos(rad), -sin(rad), 0.0, 0.0,
		sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0 ,0.0,
		0.0, 0.0, 0.0, 1.0
	};
	glUniformMatrix4fv(sRot, 1, GL_TRUE, rMatrix);
	drawSprite(a);
}


void moveUI(UI *ui, int xd, int yd, float xPow, float yPow) {
	if (ui != NULL) {
		ui->xp += xd * xPow;
		ui->yp += yd * yPow;
	}
}

void freeUI(UI *ui) {
	free(ui);
}

