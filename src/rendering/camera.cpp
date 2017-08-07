#include "rendering.h"

namespace Rendering
{
    Camera* System::_currentCamera = NULL;

    Camera::Camera(Transform* t) :
    Component(t),
    _near(0.1f), _far(100.0f), _fieldOfView(45.0f)
    {
        _forwardDirection = glm::vec3(0, 0, 1);
        _upDirection = glm::vec3(0, 1, 0);
    }

    Camera::Camera(Transform* t, float near, float far, float fov) :
    Component(t),
    _near(near), _far(far), _fieldOfView(fov)
    {
        _forwardDirection = glm::vec3(0, 0, 1);
        _upDirection = glm::vec3(0, 1, 0);
    }

    void Camera::SetAsCurrent()
    {
        System::_currentCamera = this;
    }

    // TODO: update camera matrices only when its transform changes
    void Camera::FrameUpdate()
    {
        // TODO: get position and vectors from transform
        _viewMatrix = glm::lookAt(
            (glm::vec3)_transform->_worldPosition,
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
            //(glm::vec3)_transform->_worldPosition,
            //glm::vec3(0.0f),
            //_upDirection
        );

        _projectionMatrix = glm::perspective(
            glm::radians(_fieldOfView),
            4.0f / 3.0f, // TODO: get aspect ratio of window
            _near,
            _far
        );

        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }

    glm::mat4 Camera::GetViewProjectionMatrix()
    {
        return _viewProjectionMatrix;
    }
}