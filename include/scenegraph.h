#ifndef transform_h__
#define transform_h__

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Scenegraph
{
    /*
    template <typename T, class C>
    struct UpdatingProperty
    {
        T _data;
        void (C::*_updateCallback)() = NULL;
        
        UpdatingProperty(T initialData, void (C::*callback)())
        {
            _data = initialData;
            _updateCallback = callback;
        }

        T& operator=(const T& other)
        {
            return _data = other;
            if (_updateCallback != NULL) _updateCallback();
        }
        operator T() const { return _data; }
    };
    */

    struct Transform
    {
        glm::vec3 _position;
        glm::vec3 _scale;
        glm::quat _orientation;
        Transform* _parent;
        void SetParent(Transform* parent);
        glm::mat4 _localSpaceModelMatrix;
        glm::mat4 _worldSpaceModelMatrix;
        
        // TODO: call these, as soon as position, scale, orientation, or parent changes
        void UpdateLocalSpaceModelMatrix();
        void UpdateWorldSpaceModelMatrix();

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