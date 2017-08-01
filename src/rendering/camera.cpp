#include "rendering.h"

namespace Rendering
{
    /************************************/
    /*              CAMERA              */
    /************************************/
    Camera::Camera()
    {
        _position = glm::vec3(0, 0, 0);
        _forwardDirection = glm::vec3(0, 0, 1);
        _upDirection = glm::vec3(0, 1, 0);
    }

    Camera::Camera(float near, float far, float fov, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
    {
        _near = near;
        _far = far;
        _fieldOfView = fov;
        _position = position;
        _forwardDirection = forward;
        _upDirection = up;
    }

    void Camera::Update()
    {
        _viewMatrix = glm::lookAt(
            _position,
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