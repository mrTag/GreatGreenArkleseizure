#include <iostream>
#include <stdio.h>

#include "simulator.h"
#include "velocityrule.h"
#include "GLFW\glfw3.h"

// fixes missing reference error in gcc builds
// see: http://stackoverflow.com/questions/329059/what-is-gxx-personality-v0-for/329195#329195
void *__gxx_personality_v0;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char* argv[])
{
	if (!glfwInit()){
		// init failed
		exit(EXIT_FAILURE);
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Great Green Arkleseizure", NULL, NULL);
	if (!window) {
		// window creation failed
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

    // testing simulator
	gga::Simulator simulator;
	simulator.AddSimulationRule<gga::VelocityRule>();

	int step = 0;
	while(!glfwWindowShouldClose(window)){
		// keep running
		simulator.Step();
		step++;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    exit(EXIT_SUCCESS);
}