#ifndef transform_h__
#define transform_h__

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Scenegraph
{
    struct Transform
    {
        glm::vec3 _position;
        glm::vec3 _scale;
        glm::quat _orientation;
        Transform* _parent;
        void SetParent(Transform* parent);
        glm::mat4 GetLocalSpaceModelMatrix();
        glm::mat4 GetWorldSpaceModelMatrix();

        /* TODO:
        void AddComponent(Component* c);
        void RemoveComponent(Component* c);
        Component* GetComponent<typename T>();
        int GetComponents<typename T>(Component* components_out);
        */
    };

    class Component
    {
        protected:
        Transform* _transform;
        bool _enabled;

        public:
        Component(Transform* t) : transform(t) {}
        virtual void FrameUpdate() = 0;
        virtual ~Component() {}
    };
}

#endif // transform_h__