#include "Window.h"

namespace Engine
{
    Window::Window()
    :
    window( NULL ),
    w( 0 ),
    h( 0 )
    {}

    Window::~Window()
    {
        cleanup();
    }

    void errorCallback( int error, const char* desc )
    {
        fputs( desc, stderr );
        fputs( "\n", stderr );
    }

    int Window::createWindow( int width, int height, const std::string& title, bool fullsreen )
    {
        glfwInit();
        glfwSetErrorCallback( errorCallback );

        glfwWindowHint( GLFW_RED_BITS, 8 );
        glfwWindowHint( GLFW_GREEN_BITS, 8 );
        glfwWindowHint( GLFW_BLUE_BITS, 8 );
        glfwWindowHint( GLFW_ALPHA_BITS, 8 );

        glfwWindowHint( GLFW_DEPTH_BITS, 24 );
        glfwWindowHint( GLFW_STENCIL_BITS, 8 );

        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

        window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL );

        if( !window )
        {
            fprintf( stderr, "Error: Could not create window\n" );
            return -1;
        }

        glfwGetWindowSize( this->window, &this->w, &this->h );

        glfwMakeContextCurrent( this->window );

        GLenum err = glewInit();
        if( err != GLEW_OK )
        {
            fprintf( stderr, "Error: could not initialize GLEW, %s\n", glewGetErrorString( err ) );
            return -1;
        }

        setupGL();

        return 0;
    }

    void Window::destroyWindow()
    {
        glfwDestroyWindow( window );
		window = nullptr;
    }

    int Window::setupGL()
    {
        glClearColor( 0.0, 0.0, 0.0, 1.0 );

        glViewport( 0, 0, w, h );

        return 0;
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers( this->window );
    }

    bool Window::shouldClose()
    {
        return glfwWindowShouldClose( this->window );
    }

    void Window::cleanup()
    {
		if( window )
			destroyWindow();

        glfwTerminate();
    }
}
