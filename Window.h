#ifndef WINDOW_H
#define WINDOW_H

#include <cstdio>
#include <cstdlib>

#include <iostream>

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine
{
    class Window
    {
    public:
        Window();
        ~Window();

        int createWindow( int width, int height, const std::string& title, bool fullsreen );

        void destroyWindow();

        void swapBuffers();

        bool shouldClose();

    private:
        GLFWwindow* window;

        int w, h;

        int setupGL();

        void cleanup();
    };
}

#endif // WINDOW_H
