#ifndef rendering_h__
#define rendering_h__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scenegraph.h"

namespace Rendering
{
    using namespace Scenegraph;

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