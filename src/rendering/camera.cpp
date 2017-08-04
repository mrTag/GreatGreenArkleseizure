#include "rendering.h"

namespace Rendering
{
    /************************************/
    /*              CAMERA              */
    /************************************/
    Camera::Camera(Transform* t)
    {
        // TODO: take transform as input
        _transform = t;
        _near = 0.1f;
        _far = 100.0f;
        _fieldOfView = 45.0f;
        _position = glm::vec3(0, 0, 0);
        _forwardDirection = glm::vec3(0, 0, 1);
        _upDirection = glm::vec3(0, 1, 0);
    }

    Camera::Camera(float near, float far, float fov)
    {
        // TODO: take transform as input
        _transform = t;
        _near = near;
        _far = far;
        _fieldOfView = fov;
    }

    void Camera::FrameUpdate()
    {
        // TODO: get position and vectors from transform
        _viewMatrix = glm::lookAt(
            transform->_position,
            _position + _forwardDirection,
            _upDirection
        );

        _projectionMatrix = glm::perspective(
            glm::radians(_fieldOfView),
            4.0f / 3.0f, // TODO: get aspect ratio of window
            _near,
            _far
        );
    }

    glm::mat4 Camera::GetViewProjectionMatrix()
    {
        return _projectionMatrix * _viewMatrix;
    }
}