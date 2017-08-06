#ifndef rendering_h__
#define rendering_h__

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scenegraph.h"

namespace Rendering
{
    using namespace Scenegraph;

    class Renderer : public Component
    {
        public:
        Renderer(Transform *t);
        void FrameUpdate();
    };

    class ShaderProgram
    {
        private:
        GLuint _id;
        GLuint _vertexShaderId;
        GLuint _fragmetShaderId;

        public:
        bool Init(const char* vertexShaderSource, const char* fragmentShaderSource);
        ~ShaderProgram();
    };

    class Camera : public Component
    {
        private:
        float _fieldOfView;
        float _near;
        float _far;
        glm::vec3 _position;
        glm::vec3 _forwardDirection;
        glm::vec3 _upDirection;
        glm::mat4 _viewMatrix;
        glm::mat4 _projectionMatrix;
        glm::mat4 _viewProjectionMatrix;

        public:
        Camera(Transform *t);
        Camera(Transform *t, float near, float far, float fov);
        void FrameUpdate();
        glm::mat4 GetViewProjectionMatrix();
    };
}

#endif // rendering_h__