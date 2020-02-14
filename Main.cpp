#include "Core.h"

#include "Game.h"

#ifdef _DEBUG
#include <vld.h>
#endif

Game game;

void load( Engine::InputHandler& inputHandler )
{
	glfwSetInputMode( glfwGetCurrentContext( ), GLFW_CURSOR, GLFW_CURSOR_DISABLED );
	inputHandler.addKeyBinding( Engine::KeyBinding( "jump", GLFW_KEY_SPACE, GLFW_MOUSE_BUTTON_LEFT, JOYSTICK_BUTTON_1 ) );
	inputHandler.addAxis( Engine::Axis( "Vertical", GLFW_KEY_D, GLFW_KEY_A, MOUSE_AXIS_X, JOYSTICK_AXIS_1 ) );

    game.load();
}

void tick()
{
    game.tick();
}

void render( Engine::Renderer& renderer )
{
    game.render( renderer );
}

int main( int argc, char** argv )
{
	Engine::Core* engine = new Engine::Core();

    engine->createWindow( 800, 600, "Title", false );
    engine->setFrameRate(5000);
	engine->loadFunc( &load );
	engine->updateFunc( &tick );
	engine->renderFunc( &render );

	engine->start( );

	engine->destroyWindow();

	delete engine;
}
