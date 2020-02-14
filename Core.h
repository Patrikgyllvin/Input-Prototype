#ifndef CORE_H
#define CORE_H

#include <iostream>

#include <string>

#include <chrono>
#include <thread>

#include "Window.h"
#include "Renderer.h"
#include "Time.h"
#include "InputHandler.h"

namespace Engine
{
    class Core
    {
    public:
        Core();
        ~Core();

        int createWindow( int w, int h, std::string title, bool fullscreen );
        void destroyWindow();

        void swapWindow();

        void start();
        void stop();

		void loadFunc( void( *loadFunct )( InputHandler& inputHandler ) );
        void updateFunc( void (*updFunct)() );
        void renderFunc( void (*rndrFunct)( Renderer& ) );

        void setFrameRate( int rate );

        void setVsync( bool Vsync );

    private:
        bool isWindow, isRunning;
        Window* window;

        Renderer renderer;

		InputHandler inputHandler;

        int frameRate;
        double frameTime;

        void (*loadFunction)( InputHandler& inputHandler );
        void (*updateFunction)();
        void (*renderFunction)( Renderer& );

        void run();

        void load();
        void update();
        void render();

        void cleanup();
    };
}

#endif // CORE_H
