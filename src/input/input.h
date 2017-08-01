#ifndef input_h__
#define input_h__

#include "GLFW\glfw3.h"

namespace Input
{
    class Mouse {
        private:
        static double _xpos;
        static double _ypos;

        public:
        void RegisterCursorCallbacks(GLFWwindow* window);

        private:
        static void UpdateCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    };
}

#endif // input_h__