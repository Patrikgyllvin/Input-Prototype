#include "Renderer.h"

namespace Engine
{
    Renderer::Renderer()
    {
        transMatrix = glm::mat4( 1.0f );
        rotMatrix = glm::mat4( 1.0f );
        scaleMatrix = glm::mat4( 1.0f );

        camTransMatrix = glm::mat4( 1.0f );
        camRotMatrix = glm::mat4( 1.0f );
        camScaleMatrix = glm::mat4( 1.0f );

        projectionMatrix = glm::mat4( 1.0f );
    }

    Renderer::~Renderer()
    {}

    void Renderer::load()
    {
        int w, h;

        glfwGetWindowSize( glfwGetCurrentContext(), &w, &h );

        projectionMatrix = glm::perspective( 45.0f, (float) w / (float) h, 0.01f, 100.0f );

        glGenVertexArrays( 1, &vao );
        glBindVertexArray( vao );

        standard.load( "Res/Shaders/std.vs", "Res/Shaders/std.fs" );
        standard.bind();

        glGenBuffers( 1, &quad );
        glBindBuffer( GL_ARRAY_BUFFER, quad );

        Vertex quadVerts[] = {
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            1.0, 1.0, 0.0,
            1.0, 1.0, 0.0,
            1.0, 0.0, 0.0,
            0.0, 0.0, 0.0
        };

        glBufferData( GL_ARRAY_BUFFER, sizeof( quadVerts ), quadVerts, GL_STATIC_DRAW );

        glGenBuffers( 1, &color );
        glBindBuffer( GL_ARRAY_BUFFER, color );

        glBufferData( GL_ARRAY_BUFFER, 48, NULL, GL_STREAM_DRAW );
    }

    void Renderer::translate( float x, float y, float z )
    {
        transMatrix = glm::translate( transMatrix, glm::vec3( x, y, z ) );
    }

    void Renderer::rotateX( float a )
    {
        rotMatrix = glm::rotate( rotMatrix, a, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    }

    void Renderer::rotateY( float a )
    {
        rotMatrix = glm::rotate( rotMatrix, a, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    }

    void Renderer::rotateZ( float a )
    {
        rotMatrix = glm::rotate( rotMatrix, a, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    }

    void Renderer::scale( float x, float y, float z )
    {
        scaleMatrix = glm::scale( scaleMatrix, glm::vec3( x, y, z ) );
    }

    void Renderer::loadIdentity()
    {
        transMatrix = glm::mat4( 1.0f );
        rotMatrix = glm::mat4( 1.0f );
        scaleMatrix = glm::mat4( 1.0f );
    }

    void Renderer::drawSprite()
    {
        //please re-do or at least FINISH 'n' FIX

        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glEnableVertexAttribArray( 2 );

    }

    void Renderer::drawQuad( float r, float g, float b, float a )
    {
        Color colArray[] = {
            { r, g, b, a },
            { r, g, b, a },
            { r, g, b, a },
            { r, g, b, a },
            { r, g, b, a },
            { r, g, b, a }
        };

        glm::mat4 modelMat = transMatrix * rotMatrix * scaleMatrix;
        glm::mat4 viewMat = glm::mat4( 1.0f );

        glm::mat4 MVP = projectionMatrix * viewMat * modelMat;

        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        //glEnableVertexAttribArray( 2 );

        glUniformMatrix4fv( glGetUniformLocation( standard.getID(), "MVP" ), 1, GL_FALSE, &MVP[ 0 ][ 0 ] );

        glBindBuffer( GL_ARRAY_BUFFER, quad );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );

        glBindBuffer( GL_ARRAY_BUFFER, color );
        glBufferData( GL_ARRAY_BUFFER, sizeof( colArray ), colArray, GL_STREAM_DRAW );

        glVertexAttribPointer( 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*) 0 );

        glDrawArrays( GL_TRIANGLES, 0, 6 );

        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        //glDisbleVertexAttribArray( 2 );
    }
}
