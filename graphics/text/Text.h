#ifndef TEXTRENDER
#define TEXTRENDER
#include <stdbool.h>
typedef struct textCharacter {
	unsigned int TextureID;//ID handle of the glyph texture
	//sizes
	int xSize;
	int ySize;
	//glm::ivec2 Size;
	//offsets from baseline to left/top of glyph
	int xBearing; 
	int yBearing;
	//glm::ivec2 Bearing;
	unsigned int Advance;	//Offset to advance to next glyph
} textCharacter;

typedef struct Text {
	char *str;
	float scale;
	float length;
	float height;//average height of characters
	bool centered;
	float r;
	float g;
	float b;
} Text;
#include "../glfwMain.h"
#include <ft2build.h>
#include <cglm/cglm.h>

#include FT_FREETYPE_H


textCharacter *makeTextCharacter(unsigned int texture, int xs, int ys, int xb, int yb, int advance);
void initText();
void renderText(char *string, float x, float y, float scale);
void setTextColor(float r, float g, float b);
void setOrtho();//float left, float right, float bottom, float top, float near, float far);
void drawText(Text *t, float x, float y);
Text *makeText(char *str, float scale, bool centered, float r, float g, float b);
void freeText (Text * t);
#endif
