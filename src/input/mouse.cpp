#include "input.h"

namespace Input
{
    namespace Mouse
    {
        void FrameUpdate()
        {
            previousButtonStates = currentButtonStates;
        }

        void RegisterCursorCallbacks(GLFWwindow* window)
        {
            glfwSetCursorPosCallback(window, &UpdateCursorPosCallback);
            glfwSetMouseButtonCallback(window, &UpdateMouseButtonCallback);
        }

        void UpdateCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
        {
            x = xpos;
            y = ypos;
        }

        void UpdateMouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers)
        {
            if (action == GLFW_PRESS)
            {
                currentButtonStates |= 1 << button;
            }
            else if (action == GLFW_RELEASE)
            {
                currentButtonStates &= (0xF ^ (1 << button));
            }
        }

        bool GetButton(char button)
        {
            return (currentButtonStates & (1 << button)) > 0;
        }

        bool GetButtonDown(char button)
        {
            return ((currentButtonStates & (1 << button)) > 0) && ((previousButtonStates & (1 << button)) == 0);
        }

        bool GetButtonUp(char button)
        {
            return ((currentButtonStates & (1 << button)) == 0) && ((previousButtonStates & (1 << button)) > 0);
        }
    }
}