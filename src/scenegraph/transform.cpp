#include <glm/gtc/matrix_transform.hpp>
#include <type_traits>
#include "scenegraph.h"

namespace Scenegraph
{
    Transform::Transform() :
    _parent(NULL),
    _localPosition(UpdatingProperty<glm::vec3, Transform>(glm::vec3(0.0f), this, this->UpdateModelMatrices)),
    _worldPosition(UpdatingProperty<glm::vec3, Transform>(glm::vec3(0.0f), this, this->UpdateModelMatrices)),
    _localScale(UpdatingProperty<glm::vec3, Transform>(glm::vec3(1.0f, 1.0f, 1.0f), this, this->UpdateModelMatrices)),
    _localOrientation(UpdatingProperty<glm::quat, Transform>(glm::quat(), this, this->UpdateModelMatrices)),
    _localSpaceModelMatrix(glm::mat4(1.0f)),
    _worldSpaceModelMatrix(glm::mat4(1.0f)),
    _inverseWorldSpaceModelMatrix(glm::mat4(1.0f))
    {}

    Transform::Transform(glm::vec3 position) :
    _parent(NULL),
    _localPosition(UpdatingProperty<glm::vec3, Transform>(position, this, this->LocalPostionChanged)),
    _worldPosition(UpdatingProperty<glm::vec3, Transform>(position, this, this->WorldPositionChanged)),
    _localScale(UpdatingProperty<glm::vec3, Transform>(glm::vec3(1.0f, 1.0f, 1.0f), this, this->UpdateModelMatrices)),
    _localOrientation(UpdatingProperty<glm::quat, Transform>(glm::quat(), this, this->UpdateModelMatrices)),
    _localSpaceModelMatrix(glm::mat4(1.0f)),
    _worldSpaceModelMatrix(glm::mat4(1.0f)),
    _inverseWorldSpaceModelMatrix(glm::mat4(1.0f))
    {}

    void Transform::SetParent(Transform* parent)
    {
        Transform* checkedParent = parent;
        while(checkedParent->_parent != NULL)
        {
            if (checkedParent->_parent == this)
            {
                // ERROR! circular parent relationships are not allowed!
                return;
            }
            checkedParent = checkedParent->_parent;
        }
        _parent = parent;
    }

    void Transform::LocalPostionChanged()
    {
        this->UpdateModelMatrices();
        _worldPosition.SetValueAndBypassCallback(
            glm::vec3(glm::vec4((glm::vec3)_localPosition, 1.0f) * _worldSpaceModelMatrix)
        );
    }

    void Transform::WorldPositionChanged()
    {
        _localPosition.SetValueAndBypassCallback(
            glm::vec3(glm::vec4((glm::vec3)_worldPosition, 1.0f) * _inverseWorldSpaceModelMatrix)
        );
        this->UpdateModelMatrices();
    }

    void Transform::UpdateModelMatrices()
    {
        // update local space model matrix
        _localSpaceModelMatrix = glm::mat4(1.0);
        _localSpaceModelMatrix = glm::translate(_localSpaceModelMatrix, (glm::vec3)_localPosition);
        _localSpaceModelMatrix = glm::scale(_localSpaceModelMatrix, (glm::vec3)_localScale);
        glm::mat4 rotationMatrix = glm::toMat4((glm::quat)_localOrientation);
        _localSpaceModelMatrix *= rotationMatrix;

        // update world space model matrix
        _worldSpaceModelMatrix = _localSpaceModelMatrix;
        Transform* currentParent = _parent;
        // go through all parents and multiply model matrices
        while(currentParent != NULL)
        {
            _worldSpaceModelMatrix *= currentParent->_localSpaceModelMatrix;
            currentParent = currentParent->_parent;
            if (currentParent == this) break;
        }

        _inverseWorldSpaceModelMatrix = glm::inverse(_worldSpaceModelMatrix);
    }

    template<class T>
    T* Transform::GetComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
        // TODO: implement
        return NULL;
    }
}