#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "global_constants.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "segment.hpp"
#include "snake.hpp"

class Game {

public:
    Game();
    ~Game();
    void handleEvents();
    void update();
    bool isRunning() { return running; }
    Snake * snake;
    Segment* food;

private:
    bool running;
    Segment* getValidFood();
    bool checkFoodValid(Segment* food);
};

#endif // GAME_HPP_INCLUDED
