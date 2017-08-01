#include "input.h"

namespace Input
{
    double Mouse::_xpos = 0.0;
    double Mouse::_ypos = 0.0;

    void Mouse::RegisterCursorCallbacks(GLFWwindow* window)
    {
        glfwSetCursorPosCallback(window, &UpdateCursorPosCallback);
    }

    void Mouse::UpdateCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
    {
        _xpos = xpos;
        _ypos = ypos;
    }
}