#ifndef transform_h__
#define transform_h__

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Scenegraph
{
    // Wrapper struct which binds a member variable to a member function callback.
    // Callback function is called upon assignment to the variable.
    template <typename T, class C>
    class UpdatingProperty
    {
        private:
        T _val;
        void (C::*_updateCallback)() = NULL;

        public:
        void SetValueAndBypassCallback(T newValue) { _val = newValue; }
        UpdatingProperty(T initValue, void (C::*callback)()) :
        _val(initValue),
        _updateCallback(callback)
        {}

        T& operator=(const T& other)
        {
            if (_updateCallback != NULL) _updateCallback();
            return _val = other;
        }
        operator T() const { return _val; }
    };

    class Transform
    {
        private:
        Transform* _parent;

        public:
        Transform();
        Transform(glm::vec3 position);
        UpdatingProperty<glm::vec3, Transform> _localPosition;
        UpdatingProperty<glm::vec3, Transform> _worldPosition;
        UpdatingProperty<glm::vec3, Transform> _localScale;
        UpdatingProperty<glm::quat, Transform> _localOrientation;
        glm::mat4 _localSpaceModelMatrix;
        glm::mat4 _worldSpaceModelMatrix;
        
        void SetParent(Transform* parent);
        void UpdateModelMatrices();

        /* TODO:
        void AddComponent(Component* c);
        void RemoveComponent(Component* c);
        Component* GetComponent<typename T>();
        int GetComponents<typename T>(Component* components_out);
        */

        /* TODO:
        glm::vec3 TransformPosition(glm::vec3 v);
        glm::vec3 TransformDirection(glm::vec3 v);
        glm::vec3 GetForward();
        */
    };

    class Component
    {
        protected:
        Transform* _transform;
        bool _enabled;

        public:
        Component(Transform* t) : _transform(t) {}
        virtual void FrameUpdate() = 0;
        virtual ~Component() {}
    };
}

#endif // transform_h__