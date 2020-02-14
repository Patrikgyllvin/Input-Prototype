#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "Core.h"

class Game
{
public:
    Game();
    ~Game();

    void load();

    void tick();
    void render( Engine::Renderer& renderer );
};

#endif // GAME_H
