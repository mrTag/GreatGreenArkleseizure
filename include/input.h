#ifndef input_h__
#define input_h__

#include "GLFW/glfw3.h"

namespace Input
{
    namespace Mouse
    {
        static double x = 0.0;
        static double y = 0.0;
        static char currentButtonStates = 0;
        static char previousButtonStates = 0;

        void FrameUpdate();

        void RegisterCursorCallbacks(GLFWwindow* window);
        void UpdateCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        void UpdateMouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);

        bool GetButton(char button);
        bool GetButtonDown(char button);
        bool GetButtonUp(char button);
    }
}

#endif // input_h__