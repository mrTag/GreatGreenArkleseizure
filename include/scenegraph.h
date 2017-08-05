#ifndef transform_h__
#define transform_h__

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#define CALL_MEMBER_FN(ptrToObject, ptrToMember) ((ptrToObject)->*(ptrToMember))

namespace Scenegraph
{
    // Wrapper struct which binds a member variable to a member function callback.
    // Callback function is called upon assignment to the variable.
    template <typename T, class C>
    class UpdatingProperty
    {
        using CallbackFunction = void (C::*)();
        private:
        T _val;
        C* _objPtr;
        CallbackFunction _updateCallback = NULL;

        public:
        void SetValueAndBypassCallback(T newValue) { _val = newValue; }
        UpdatingProperty(T initValue, C* obj, CallbackFunction callback) :
        _val(initValue),
        _objPtr(obj),
        _updateCallback(callback)
        {}

        T& operator=(const T& other)
        {
            _val = other;
            if (_updateCallback != NULL) CALL_MEMBER_FN(_objPtr, _updateCallback)();
            return _val;
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
        glm::mat4 _inverseWorldSpaceModelMatrix;
        
        void SetParent(Transform* parent);
        void LocalPostionChanged();
        void WorldPositionChanged();
        void UpdateModelMatrices();

        template<class T>
        T* GetComponent();
        /* TODO:
        void AddComponent(Component* c);
        void RemoveComponent(Component* c);
        int GetComponents<typename T>(T* components_out);
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