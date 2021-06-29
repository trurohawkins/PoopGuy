#include "glfwMain.h"

GLuint screenWidth = 800*8/5, screenHeight = 450*8/5;
//GLFWwindow *window;
Screen *curScreen;
GLuint curShaderProgram;

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
	//start glew extension handle
	glewExperimental = GL_TRUE;// I think it must be under the make context current!
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	printf("OpenGL - %i.%i.%i\n", major, minor, rev);

	//tell GL to only draw onto a pixel if shape is cloer to the viewer
	glEnable(GL_DEPTH_TEST);//enable depther testing
	glDepthFunc(GL_LESS); //depth testing interpets a smaller value as "closer"
	curShaderProgram = makeShaderProgram("graphicsSource/matVS.glsl", "graphicsSource/simpFS.glsl");
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


void glfwWindowSizeCallback(GLFWwindow *window, int width, int height) {
	curScreen->width = width;
	curScreen->height = height;
	glViewport(0, 0, curScreen->width, curScreen->height);
}

Screen *getWindow() {
	return curScreen;
}

GLuint getSP() {
	return curShaderProgram;
}
