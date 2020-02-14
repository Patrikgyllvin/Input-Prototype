#include "Game.h"
float r = 0;
int i = 0;
Game::Game()
{}

Game::~Game()
{}

void Game::load()
{
}

void Game::tick()
{
	r += 10 * Engine::InputHandler::getAxis("Vertical");
}

void Game::render( Engine::Renderer& renderer )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    renderer.loadIdentity();
	renderer.translate( 0, 0, -10 );
	renderer.rotateX( r );
	renderer.rotateY( r );
    renderer.rotateZ( r );

    renderer.drawQuad( 127, 127, 255, 255 );

    renderer.loadIdentity();
	renderer.translate( -1, 1, -10 );
	renderer.rotateX( r );
	renderer.rotateY( r );
    renderer.rotateZ( r );

    renderer.drawQuad( 255, 127, 63, 255 );
}
