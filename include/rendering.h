#ifndef rendering_h__
#define rendering_h__

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scenegraph.h"

namespace Rendering
{
    using namespace Scenegraph;
    
    class Camera;
    class ShaderProgram;
    class Renderer;

    class System
    {
        friend Camera;
        friend Renderer;
        
        private:
        System() {}
        static Camera* _currentCamera;
        static void RegisterRenderer();
        static void UnregisterRenderer();

        public:
        static void RenderScene();
    };

    class ShaderProgram
    {
        private:
        GLuint _id;
        GLuint _vertexShaderId;
        GLuint _fragmentShaderId;
        GLuint _vertexBufferId;
        GLuint _viewProjMatrixId;
        GLuint _modelMatrixID;
        GLuint _colorID;

        public:
        bool InitProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
        void InitBuffers(size_t vertexBufferSize, GLfloat* vertexBufferPtr);
        GLuint GetID() { return _id; }
        ~ShaderProgram();
    };

    class Renderer : public Component
    {
        friend System;

        private:
        ShaderProgram* _shader;

        public:
        Renderer(Transform *t);
        void FrameUpdate();
        
        private:
        void Render();
    };

    class Camera : public Component
    {
        private:
        float _fieldOfView;
        float _near;
        float _far;
        glm::vec3 _position;
        glm::vec3 _forwardDirection;
        glm::vec3 _upDirection;
        glm::mat4 _viewMatrix;
        glm::mat4 _projectionMatrix;
        glm::mat4 _viewProjectionMatrix;

        public:
        Camera(Transform *t);
        Camera(Transform *t, float near, float far, float fov);
        void FrameUpdate();
        void SetAsCurrent();
        glm::mat4 GetViewProjectionMatrix();
    };
}

#endif // rendering_h__