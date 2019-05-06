#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "global_constants.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "snake.hpp"

class Game {

public:
    Game(const char * title, int posx, int posy, int width,
      int height, bool maximised);
    ~Game();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning() { return running; }

private:
    SDL_Window * window;
    SDL_Renderer * renderer;
    bool running;
    Snake * snake;

};

#endif // GAME_HPP_INCLUDED
