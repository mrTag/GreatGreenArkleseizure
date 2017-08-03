#include "scenegraph.h"

namespace Scenegraph
{
    void Transform::SetParent(Transform* parent)
    {
        // TODO: check for circular parenting! cycles are nor allowed!
        _parent = parent;
    }

    void Transform::UpdateLocalSpaceModelMatrix()
    {
        _localSpaceModelMatrix = modelMatrix(1.0);
        _localSpaceModelMatrix = glm::translate(_localSpaceModelMatrix, _position);
        _localSpaceModelMatrix = glm::scale(_localSpaceModelMatrix, _scale);
        glm::mat4 rotationMatrix = quaternion::toMat4(_orientation);
        _localSpaceModelMatrix *= rotationMatrix;
    }

    void Transform::UpdateWorldSpaceModelMatrix()
    {
        _worldSpaceModelMatrix = GetLocalSpaceModelMatrix();
        Transform* currentParent = _parent;
        // go through all parents and multiply model matrices
        while(_currentParent != NULL)
        {
            _worldSpaceModelMatrix *= _currentParent.GetLocalSpaceModelMatrix();
            _currentParent = _currentParent._parent;
            if (_currentParent == this) break;
        }
    }
}