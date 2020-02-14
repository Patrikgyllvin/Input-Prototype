#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Shader.h"

#include <iostream>

namespace Engine
{
    typedef struct {
        GLfloat x, y, z;
    } Vertex;

    typedef struct {
        GLubyte r, g, b, a;
    } Color;

    typedef struct {
        GLfloat u, v;
    } UV;

    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        void load();


        void translate( float x, float y, float z );

        void rotateX( float a );
        void rotateY( float a );
        void rotateZ( float a );

        void scale( float x, float y, float z );

        void loadIdentity();

        void drawSprite();
        void drawQuad( float r, float g, float b, float a );
    private:
        glm::mat4 transMatrix;
        glm::mat4 rotMatrix;
        glm::mat4 scaleMatrix;

        glm::mat4 camTransMatrix;
        glm::mat4 camRotMatrix;
        glm::mat4 camScaleMatrix;

        glm::mat4 projectionMatrix;

        GLuint vao, quad, color, uv;

        Shader standard;
    };
}

#endif // RENDERER_H
