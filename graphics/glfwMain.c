#include "glfwMain.h"
#include "shaders/glslLib.c"

GLuint screenWidth = 800*8/5, screenHeight = 450*8/5;
//GLFWwindow *window;
Screen *curScreen;
GLuint baseShaderProgram;
GLuint texShaderProgram;
GLuint tileShaderProgram;


int initializeGLFW() {
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
	//use OpenGL 3.3 set minimum so we dont use depreceated functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// look into the specifics of these functions
	//got them from depreceated tutroial(had to update function calls and arg names

	//window = glfwCreateWindow(screenWidth, screenHeight, "poop", glfwGetPrimaryMonitor(), NULL); full screen
	//window = glfwCreateWindow(screenWidth, screenHeight, "poop", NULL, NULL);
	GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "poop", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	} else {
		glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
		curScreen = (Screen*)calloc(sizeof(Screen), 1);
		curScreen->window = window;
		curScreen->width = screenWidth;
		curScreen->height = screenHeight;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	printf("OpenGL - %i.%i.%i\n", major, minor, rev);

	//tell GL to only draw onto a pixel if shape is cloer to the viewer
	// I turned it off because the sprites are all the same distance from camera
	//glEnable(GL_DEPTH_TEST);//enable depther testing
	//glDepthFunc(GL_LESS); //depth testing interpets a smaller value as "closer"
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	baseShaderProgram = makeShaderProgram(matVS, matFS);
	//texShaderProgram = makeShaderProgramFile("graphics/shaders/texVS.glsl", "graphics/shaders/texFS.glsl");
	texShaderProgram = makeShaderProgram(singleTexVS, singleTexFS);
	tileShaderProgram = makeShaderProgram(texVS, texFS);
}

GLuint squareVao2d() {
	float square[12] = {
		-0.5, 0.5, 
		0.5, 0.5, 
		0.5, -0.5, 
		-0.5, 0.5, 
		0.5, -0.5, 
		-0.5, -0.5, 
	};
	return makeVao2d(square, 12);
}

GLuint lineVao2d(int lineType) {
	float line[4];
	int val = 1;
	for (int i = 0; i < 4; i++) {
		if (i % 2 == lineType) {
			line[i] = 0;
		} else {
			line[i] = val;
			val *= -1;
		}
	}
	return makeVao2d(line, 4);
}

GLuint makeVao2d(float *shape, int len) {
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * len, shape, GL_STATIC_DRAW);
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);//points = 0 on vao
	glEnableVertexAttribArray(0);
	return vao;	
}

GLuint makeSpriteVao(float sx, float sy) {
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  sx, 1,
		0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f, sx, 1-sy,
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 0, 1-sy,
		-0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 0, 1
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint vbo, vao, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//points/pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	return vao;
}

void glfwWindowSizeCallback(GLFWwindow *window, int width, int height) {
	curScreen->width = width;
	curScreen->height = height;
	glViewport(0, 0, curScreen->width, curScreen->height);
}

Screen *getWindow() {
	return curScreen;
}

GLuint getSP(int shader) {
	if (shader == 0) {
		return baseShaderProgram;
	} else if (shader == 1) {
		return texShaderProgram;
	} else {
		return tileShaderProgram;
	}
}
