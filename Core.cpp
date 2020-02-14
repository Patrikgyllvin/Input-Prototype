#include "Core.h"

namespace Engine
{
    Core::Core()
    :
	isWindow( false ),
    isRunning( false ),
    window( nullptr ),
    renderer(),
	inputHandler(),
    frameRate( 5000 ),
    frameTime( 1.0 / (double)frameRate ),
    loadFunction( nullptr ),
    updateFunction( nullptr ),
    renderFunction( nullptr )
	{
		Time t( &frameTime );
    }

    Core::~Core()
    {
        cleanup();
    }

    void Core::cleanup()
    {
		delete window;
    }

    int Core::createWindow( int w, int h, std::string title, bool fullscreen )
    {
        if( isWindow )
        {
            fputs( "Cannot create window: A window already exists!\n", stdout );
            return -1;
        }

		if( !window )
			window = new Window();

        window->createWindow( w, h, title, fullscreen );

		isWindow = true;

        return 0;
    }

    void Core::destroyWindow()
    {
		if( isWindow )
			window->destroyWindow();

		isWindow = false;
    }

    void Core::swapWindow()
    {
		if( isWindow )
			this->window->swapBuffers();
    }

    void Core::setVsync( bool Vsync )
    {
        glfwSwapInterval( Vsync );
    }

    void Core::setFrameRate( int rate )
    {
        this->frameRate = rate;
    }

    void Core::start()
    {
        if( !isWindow )
        {
            fputs( "Create a window before running!\n", stderr );
            return;
        }
        if( isRunning )
        {
            fputs( "Already running!\n", stdout );
            return;
        }

        run();
    }

    void Core::stop()
    {
        if( isRunning )
            isRunning = false;
    }

    void Core::run()
    {
        isRunning = true;

        load();

        int frames = 0;
        double frameCounter = 0.0;

        int lastFrameRate = frameRate;
        frameTime = 1.0 / (double)frameRate;

        double lastTime = Time::getTime();
        double deltaTime;
        double currTime;

        double unprocessedTime = 0.0;

        bool shouldRender;

        while( isRunning )
        {
            if( lastFrameRate != frameRate )
            {
                frameTime = 1.0 / (double)frameRate;
                lastFrameRate = frameRate;
            }

            shouldRender = false;

            currTime = Time::getTime();
            deltaTime = currTime - lastTime;
            lastTime = currTime;

            unprocessedTime += deltaTime;
            frameCounter += deltaTime;

            while( unprocessedTime > frameTime )
            {
                shouldRender = true;

                unprocessedTime -= frameTime;

                if( window->shouldClose() )
                    stop();

				glfwPollEvents();
                update();

				inputHandler.update();

                if( frameCounter > Time::TICKS_PER_SEC )
                {
                    fprintf( stdout, "FPS: %i\n", frames );
                    frames = 0;
                    frameCounter = 0.0;
                }
            }
            if( shouldRender )
            {
                render();
                frames++;
            }
            else
            {
                std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
            }
        }
    }

    void Core::load()
    {
        renderer.load();

		inputHandler.refreshJoysticks();

        if( this->loadFunction )
            loadFunction( inputHandler );
    }

    void Core::update()
    {
        if( this->updateFunction )
            updateFunction();
    }

    void Core::render()
    {
        if( this->renderFunction )
            renderFunction( this->renderer );

        swapWindow();
    }

    void Core::loadFunc( void (*loadFunct)( InputHandler& ) )
    {
        this->loadFunction = loadFunct;
    }

    void Core::updateFunc( void (*updFunct)() )
    {
        this->updateFunction = updFunct;
    }

    void Core::renderFunc( void (*rndrFunct)( Renderer& ) )
    {
        this->renderFunction = rndrFunct;
    }
}
