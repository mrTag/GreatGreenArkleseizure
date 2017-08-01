#ifndef transform_h__
#define transform_h__

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace Scenegraph {
    struct Transform {
        glm::vec3 _position;
        glm::quat _orientation;
        glm::vec3 _scale;
        Transform* _parent;
        Transform* _children;
        unsigned int _cildCount;
    };
}

#endif // transform_h__