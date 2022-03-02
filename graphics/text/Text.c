#include "Text.h"
textCharacter **alphabet;
unsigned int VAO,VBO;

textCharacter *makeTextCharacter(unsigned int texture, int xs, int ys, int xb, int yb, int advance) {
	textCharacter *tc = (textCharacter*)calloc(sizeof(textCharacter), 1);
	tc->TextureID = texture;
	tc->xSize = xs;
	tc->ySize = ys;
	tc->xBearing = xb;
	tc->yBearing = yb;
	tc->Advance = advance;
	return tc;
}

void initText() {
	Screen *screen = getWindow();
	GLuint textShader = getSP(3);
	glUseProgram(textShader);
	float projection [] = {
		0.001563, 0.0, 0.0, 0.0,
		0.0, 0.002778, 0.0, 0.0,
		0.0, 0.0, -1.0, 0.0,
		-1.0, -1.0, 0.0, 1.0
	};

	glUniformMatrix4fv(glGetUniformLocation(textShader, "projection"), 1, GL_FALSE, projection);
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		printf("Freetype error couldnt init\n");
		return;
	}
	FT_Face face;
	if (FT_New_Face(ft, "resources/fonts/Arial.ttf", 0, &face)) {
		printf("Freetype couldnt load font\n");
		return; 
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	alphabet = (textCharacter**)calloc(sizeof(textCharacter*), 128);	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			printf("failed to load glyph %c\n", c);
			continue;
		}
		//generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		//set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		alphabet[c] = makeTextCharacter(texture, face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap_left, face->glyph->bitmap_top, face->glyph->advance.x);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void renderText(char *string, float x, float y, float scale) {
	GLuint textShader = getSP(3);
	glUseProgram(textShader);
	glUniform3f(glGetUniformLocation(textShader, "textColor"), 0.5, 0.8, 0.2);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	char *c = string;
	//printf("begin\n");
	while (*c != '\0') {
	//	printf("char: %c\n", *c);
		textCharacter *ch = alphabet[*c];
		float xpos = x + ch->xBearing * scale;
		float ypos = y - (ch->ySize - ch->yBearing) * scale;
		//printf("placing at %f, %f\n", xpos, ypos);
		float w = ch->xSize * scale;
		float h = ch->ySize * scale;
		//printf("w&h %f&%f\n", w, h);

		float vertices[6][4] = {
			{xpos,		 ypos + h,	0.0, 0.0},
			{xpos,		 ypos,			0.0, 1.0},
			{xpos + w, ypos,			1.0, 1.0},

			{xpos,		 ypos + h,	0.0, 0.0},
			{xpos + w, ypos,			1.0, 1.0},
			{xpos + w, ypos + h,	1.0, 0.0}
		};
		//render glyoh texture over quad
		glBindTexture(GL_TEXTURE_2D, ch->TextureID);
		//update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//now advancve cursors for next glyph (note that the advance is 1/64 pixels)
		x += (ch->Advance >> 6) * scale;//butshift by 6 to get value in pixels (2^6 = 64)
		c++;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void setOrtho(float left, float right, float bottom, float top, float near, float far) {
	GLuint textShader = getSP(3);
	glUseProgram(textShader);
	float mid_x = (left + right) / 2; //tt = 0.5
	float mid_y = (bottom + top) / 2;
	float mid_z = (near + far) / 2;
	/*
	float projection [] = {
		1.0, 0.0, 0.0, -mid_x,
		0.0, 1.0, 0.0, -mid_y,
		0.0, 0.0, 1.0, -mid_z,
		0.0, 0.0, 0.0, 1.0
	};
	*/
	glUseProgram(textShader);
	float projection [] = {
		0.001563, 0.0, 0.0, 0.0,
		0.0, 0.002778, 0.0, 0.0,
		0.0, 0.0, -1.0, 0.0,
		-1.0, -1.0, 0.0, 1.0
	};

	glUniformMatrix4fv(glGetUniformLocation(textShader, "projection"), 1, GL_FALSE, projection);
	Screen *screen = getWindow();
 			//glm_ortho(0.0f, (float)(screen->width), 0.0f, (float)(screen->height), 0.1, 1000, dest);
}

