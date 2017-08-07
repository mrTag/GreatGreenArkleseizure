#include <iostream>
#include "rendering.h"

using namespace std;

namespace Rendering
{
    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(_id);
    }

    bool ShaderProgram::InitProgram(const char *vertexShaderSource, const char *fragmentShaderSource)
    {
        GLint compile_ok = GL_FALSE;
        GLint link_ok = GL_FALSE;

        // compile vertex shader
        _vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(_vertexShaderId, 1, &vertexShaderSource, NULL);
        glCompileShader(_vertexShaderId);
        glGetShaderiv(_vertexShaderId, GL_COMPILE_STATUS, &compile_ok);
        if (!compile_ok)
        {
            cerr << "Error in vertex shader" << endl;
            return false;
        }

        // compile fragment shader
        _fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(_fragmentShaderId, 1, &fragmentShaderSource, NULL);
        glCompileShader(_fragmentShaderId);
        glGetShaderiv(_fragmentShaderId, GL_COMPILE_STATUS, &compile_ok);
        if (!compile_ok)
        {
            cerr << "Error in fragment shader" << endl;
            return false;
        }

        // compile GLSL program
        _id = glCreateProgram();
        glAttachShader(_id, _vertexShaderId);
        glAttachShader(_id, _fragmentShaderId);
        glLinkProgram(_id);
        glGetProgramiv(_id, GL_LINK_STATUS, &link_ok);
        if (!link_ok)
        {
            cerr << "Error in glLinkProgram" << endl;
            return false;
        }

        return true;
    }

    void ShaderProgram::InitBuffers(size_t vertexBufferSize, GLfloat *vertexBufferPtr)
    {
        glGenBuffers(1, &_vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertexBufferPtr, GL_STATIC_DRAW);

        _viewProjMatrixId = glGetUniformLocation(_id, "viewProjMatrix");
	    _modelMatrixID = glGetUniformLocation(_id, "modelMatrix");
	    _colorID = glGetUniformLocation(_id, "tri_color");
    }
}