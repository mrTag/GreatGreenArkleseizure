#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <assert.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include "memory/allocators.h"
#include "scenegraph.h"
#include "input.h"
#include "rendering.h"

using namespace std;

// fixes missing reference error in gcc builds
// see: http://stackoverflow.com/questions/329059/what-is-gxx-personality-v0-for/329195#329195
void *__gxx_personality_v0;

// global variables
GLuint program;
Scenegraph::Transform camera_transform(glm::vec3(3, 3, 6));
Rendering::Camera camera(&camera_transform, 0.1f, 100.0f, 45.0f);
GLuint matrixID;
GLuint colorID;
GLuint vertexID;
static const GLfloat triangle_vertices[] = {
	0.0f, 0.8f, 0.0f,
	-0.8f, -0.8f, 0.0f,
	0.8f, -0.8f, 0.0f
};

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
		"#version 330 core\n"
		"layout(location = 0) in vec3 vertexPosition_modelspace;"
		"uniform mat4 MVP;"
		"void main(void) {"
		"  gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);"
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
		"#version 330 core\n"
		"uniform vec3 tri_color;"
		"out vec3 color;"
		"void main(void) {"
		"  color = tri_color;"
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

	glGenBuffers(1, &vertexID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	matrixID = glGetUniformLocation(program, "MVP");
	colorID = glGetUniformLocation(program, "tri_color");

	return true;
}

void render(GLFWwindow* window)
{
	glm::mat4 mvp = camera.GetViewProjectionMatrix();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

	glm::vec3 color(1.0, 0.0, 0.0);
	if (Input::Mouse::GetButton(1))
	{
		color = glm::vec3(1.0, 1.0, 0.0);
	}
	else if (Input::Mouse::GetButton(0))
	{
		color = glm::vec3(0.0, 1.0, 0.0);
	}
	glUniform3fv(colorID, 1, &color[0]);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glVertexAttribPointer(
		0,			// attribute
		3,			// number of elements (x, y, z)
		GL_FLOAT,	// element type
		GL_FALSE,	// take values as-is?
		0,			// no extra data between each position
		(void*)0	// pointer to triangle array
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
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
		camera_transform._localPosition = (glm::vec3)camera_transform._localPosition + glm::vec3(0.0f, 0.0f, -0.1f);
		camera.FrameUpdate();
		Input::Mouse::FrameUpdate();
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

	Input::Mouse::RegisterCursorCallbacks(window);

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