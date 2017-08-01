#ifndef rendering_h__
#define rendering_h__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Rendering
{
    class Camera
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

        public:
        Camera();
        Camera(float near, float far, float fov, glm::vec3 position, glm::vec3 forward, glm::vec3 up);
        void Update();
        glm::mat4 GetViewProjectionMatrix();
    };
}

#endif // rendering_h__