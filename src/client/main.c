#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "client/game.h"

#define SLICE_TIME 1.f
#define FRAME_TIME 1.f

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}

	Game* g = (Game*)glfwGetWindowUserPointer(window);

	if(action == GLFW_PRESS || action == GLFW_REPEAT) {
		gameKeyPressed(g, key);
	}
	else if(action == GLFW_RELEASE) {
		gameKeyReleased(g, key);
	}
}

void mouse_callback(GLFWwindow* window, double x, double y) {
	Game* g = (Game*)glfwGetWindowUserPointer(window);
	gameMouseMoved(g, (float)x, (float)y);
}

int main(int argc, char** argv) {
	if(!glfwInit()) {
		fprintf(stderr, "Error: GLFW: can not initialize\n");
		return 1;
	}

	glfwWindowHint(GLFW_RESIZABLE, 0);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Tron", 0, 0);
	if(!window) {
		fprintf(stderr, "Error: GLFW: can not create window\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	GLenum err = glewInit();
	if(err != GLEW_OK) {
		fprintf(stderr, "Error: GLEW: %s\n", glewGetErrorString(err));

		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	printf("GLEW %s, OpenGL %s\n", glewGetString(GLEW_VERSION), glGetString(GL_VERSION));

	Game g = gameInit(1280, 720);
	glfwSetWindowUserPointer(window, &g);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	double lastFps = 0.f;
	double last = 0.f;
	double currSlice = 0.f;

	while(!glfwWindowShouldClose(window)) {
		double start = glfwGetTime();
		currSlice += last;

		glfwPollEvents();

		/*while(currSlice >= SLICE_TIME) {
			gameUpdate(&g, FRAME_TIME);
			currSlice -= SLICE_TIME;
		}*/

		gameUpdate(&g, last);
		gameRender(&g);
		glfwSwapBuffers(window);

		double now = glfwGetTime();
		double elapsed = now - start;
		last = elapsed;

		if(now - lastFps >= 1.0) {
			char title[14];
			sprintf(title, "Tron - %02d FPS", (int)(1.0 / elapsed));
			glfwSetWindowTitle(window, title);

			lastFps = now;
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
