#include "scenegraph.h"

namespace Scenegraph
{
    void Transform::SetParent(Transform* parent)
    {
        // TODO: check for circular parenting! cycles are nor allowed!
        _parent = parent;
    }

    glm::mat4 Transform::GetLocalSpaceModelMatrix()
    {
        glm::mat4 modelMatrix(1.0);
        modelMatrix = glm::translate(modelMatrix, _position);
        modelMatrix = glm::scale(modelMatrix, _scale);
        glm::mat4 rotationMatrix = quaternion::toMat4(_orientation);
        modelMatrix *= rotationMatrix;
        return modelMatrix;
    }

    glm::mat4 Transform::GetWorldSpaceModelMatrix()
    {
        glm::mat4 modelMatrix = GetLocalSpaceModelMatrix();
        Transform* currentParent = _parent;
        // go through all parents and multiply model matrices
        while(_currentParent != NULL)
        {
            modelMatrix *= _currentParent.GetLocalSpaceModelMatrix();
            _currentParent = _currentParent._parent;
            if (_currentParent == this) break;
        }
        return modelMatrix;
    }
}