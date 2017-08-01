#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <assert.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include "memory/allocators.h"
#include "scenegraph/transform.h"
#include "input/input.h"
#include "rendering/rendering.h"

using namespace std;

// fixes missing reference error in gcc builds
// see: http://stackoverflow.com/questions/329059/what-is-gxx-personality-v0-for/329195#329195
void *__gxx_personality_v0;

// global variables
GLuint program;
GLint attribute_coord2d;
Input::Mouse mouseInput;
Rendering::Camera camera (
	0.1f, 100.0f, 45.0f,
	glm::vec3(0, 0, -4),
	glm::vec3(0, 0, 0),
	glm::vec3(0, 1, 0)
);
GLuint matrixID;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool init_resources(void)
{
	GLint compile_ok = GL_FALSE;
	GLint link_ok = GL_FALSE;
	
	// compile vertex shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char* vs_source =
		"#version 120\n"
		"uniform mat4 MVP;"
		"attribute vec2 coord2d;"
		"void main(void) {"
		"  gl_Position = MVP * vec4(coord2d, 0.0, 1.0);"
		"}";
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok) {
		cerr << "Error in vertex shader" << endl;
		return false;
	}

	// compile fragment shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fs_source =
		"#version 120\n"
		"void main(void) {"
		"  gl_FragColor[0] = 0.0;"
		"  gl_FragColor[1] = 0.8;"
		"  gl_FragColor[2] = 0.0;"
		"}";
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok) {
		cerr << "Error in fragment shader" << endl;
		return false;
	}

	// compile GLSL program
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		cerr << "Error in glLinkProgram" << endl;
		return false;
	}

	const char* attribute_name = "coord2d";
	attribute_coord2d = glGetAttribLocation(program, attribute_name);
	if (attribute_coord2d == -1) {
		cerr << "Could not bind attribute " << attribute_name << endl;
		return false;
	}

	matrixID = glGetUniformLocation(vs, "MVP");

	return true;
}

void render(GLFWwindow* window)
{
	glm::mat4 mvp = camera.GetViewProjectionMatrix();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	// TODO: make this a 3d triangle!
	glEnableVertexAttribArray(attribute_coord2d);
	GLfloat triangle_vertices[] = {
		0.0f, 0.8f, 0.0f,
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0,0f
	};

	glVertexAttribPointer(
		attribute_coord2d,	// attribute
		2,					// number of elements (x, y)
		GL_FLOAT,			// element type
		GL_FALSE,			// take values as-is?
		0,					// no extra data between each position
		triangle_vertices	// pointer to triangle array
		);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(attribute_coord2d);
	glfwSwapBuffers(window);
}

void free_resources()
{
	glDeleteProgram(program);
}

void mainLoop(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		render(window);
	}
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

	mouseInput.RegisterCursorCallbacks(window);

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		cerr << "Error: glewInit: " << glewGetErrorString(glew_status) << endl;
		exit(EXIT_FAILURE);
	}

	if (!init_resources())
		exit(EXIT_FAILURE);

	mainLoop(window);

	free_resources();
	glfwDestroyWindow(window);
	glfwTerminate();
    exit(EXIT_SUCCESS);
}