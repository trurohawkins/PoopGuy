#include "FormGlfw.h"

float centerX;
float centerY;
int frameX = 50;
int frameY = 50;
bool gridOn = false;

void updateLoop() {
	//GLFWwindow *window
	Screen *screen = getWindow();
	GLuint squa = squareVao2d();
	GLuint vLi = lineVao2d(0);
	//GLuint hLi = lineVao2d(1);
	GLuint shaderProgram = getSP();//makeShaderProgram("graphicsSource/matVS.glsl", "graphicsSource/simpFS.glsl");
	if (shaderProgram != 0) {
		int tMat = glGetUniformLocation(shaderProgram, "tMat");
		if (tMat == -1) {
			printf("vert doesnt have a var tMat\n");
		}
		int sMat = glGetUniformLocation(shaderProgram, "sMat");
		if (sMat == -1) {
			printf("vert doesnt have a var sMat\n");
		}
		int rMat = glGetUniformLocation(shaderProgram, "rMat");
		if (rMat == -1) {
			printf("vert doesnt have a var rMat\n");
		}
		int drawColor = glGetUniformLocation(shaderProgram, "inputColor");
		if (drawColor == -1) {
			printf("frag doesnt have a var drawColor\n");
		}
		float matrix[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(rMat, 1, GL_TRUE, matrix);
		World *w = getWorld();
		while(!glfwWindowShouldClose(screen->window)) {
			glClearColor(0.0, 0.4, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			if (gridOn) {
				drawGrid(matrix, tMat, sMat, rMat, drawColor, vLi);
			}
			drawWorld(w, matrix, tMat, sMat, rMat, drawColor, squa);

			glfwPollEvents();
			if(glfwGetKey(screen->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(screen->window, 1);
			}
			actorListDo();
			setCenter(getPlayer()->me->body->pos);
			glfwSwapBuffers(screen->window);
		}
	}
}

void drawWorld(World *w, float *mat, int tMat, int sMat, int rMat, int color, GLuint squa) {
		float matrix[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
	glUniformMatrix4fv(rMat, 1, GL_TRUE, matrix);

	int fx = frameX/2;
	int fy = frameY/2;
	int cx = clamp(centerX, fx, w->x - fx - 1);
	int cy = clamp(centerY, fy, w->y - fy - 1);
	float xSize = 2.0f / frameX;//(float)scr->width / 10000;
	float ySize = 2.0f / frameY;//(float)scr->height /10000;
	matrix[0] = xSize;
	matrix[5] = ySize;
	glUniformMatrix4fv(sMat, 1, GL_TRUE, matrix);
	glBindVertexArray(squa);
	for (int x = 0; x < frameX; x++) {
		mat[3] = (-1 + xSize/2) + (x * xSize);
		for (int y = 0; y < frameY; y++) {
			int xp = x + (cx-fx);
			int yp = y + (cy-cy);
			if (xp >= 0 && xp < w->x && yp >= 0 && yp < w->y) {
				if (w->map[xp][yp] != NULL) {
					mat[7] = (-1 + ySize/2) + (y * ySize);	
					glUniformMatrix4fv(tMat, 1, GL_TRUE, mat);
					float *fCol = w->map[xp][yp]->color;
					glUniform4f(color, fCol[0], fCol[1], fCol[2], 1.0);
					glDrawArrays(GL_TRIANGLES, 0, 6);
				}
			}
		}
	}
}

void drawGrid(float *mat, int tMat, int sMat, int rMat, int color, GLuint vLi) {
	float xSize = 2.0f / frameX;//(float)scr->width / 10000;
	float ySize = 2.0f / frameY;//(float)scr->height /10000;
		float matrix[] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};
	
	glUniformMatrix4fv(sMat, 1, GL_TRUE, matrix);
	glUniformMatrix4fv(rMat, 1, GL_TRUE, matrix);
	mat[7] = 0;
	glUniform4f(color, 0, 0, 0, 1.0);
	glBindVertexArray(vLi);
	for (int x = 0; x < frameX; x++) {
		mat[3] = -1 + (x * xSize);
		glUniformMatrix4fv(tMat, 1, GL_TRUE, mat);
		glDrawArrays(GL_LINES, 0, 2);	
	}

	mat[3] = 0;
	float rMatrix[] = {
		0, -1, 0, 0,
		1, 0, 0, 0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	glUniformMatrix4fv(rMat, 1, GL_TRUE, rMatrix);
	for (int y = 0; y < frameY; y++) {
		mat[7] = -1 + (y * ySize);
		glUniformMatrix4fv(tMat, 1 ,GL_TRUE, mat);
		glDrawArrays(GL_LINES, 0, 2);
	}
}

void setCenter(float cp[2]) {
	centerX = cp[0];
	centerY = cp[1];
}

void setFrame(int x, int y) {
	frameX = x;
	frameY = y;
}

void setGrid(bool state) {
	gridOn = state;
}

void exitGame() {
	freeWorld();
	freeJoyList();
}
