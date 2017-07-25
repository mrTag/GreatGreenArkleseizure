#ifndef transform_h__
#define transform_h__

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace scenegraph {
    class transform {
        private:
        glm::vec3 _position;
        glm::quat _orientation;
        glm::vec3 _scale;
        transform* _parent;
        transform* _children;
        unsigned int _cildCount;
    };
}

#endif // transform_h__