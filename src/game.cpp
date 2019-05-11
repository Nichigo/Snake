#include "game.hpp"

Game::Game() {

    running  = false;
    snake    = nullptr;

    running = true;
    snake = new Snake(GRID / 2, GRID / 2, rand() % 4);
    food = getValidFood();
}

Game::~Game() {
    delete snake;
    delete food;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    snake->setDirection(DIR_NORTH);
                    break;
                case SDLK_DOWN:
                    snake->setDirection(DIR_SOUTH);
                    break;
                case SDLK_LEFT:
                    snake->setDirection(DIR_WEST);
                    break;
                case SDLK_RIGHT:
                    snake->setDirection(DIR_EAST);
                    break;
                case SDLK_RETURN:
                    if (!snake->isAlive()) running = false;
                    break;
                default:
                    break;
            }
        }
        else if (event.type == SDL_QUIT) running = false;
    }
}

void Game::update() {
    if (snake->isAlive()) {
        snake->checkCollision();
        if(snake->checkAndEatFood(food))
        {
            delete food;
            food = getValidFood();
        }

        snake->move();
    }
}

/*
void Game::render() {
    SDL_RenderClear(renderer);
    snake->render();
    if (!snake->isAlive()) {
        SDL_Rect r;
        r.w = G_SIZE-200;
        r.h = G_SIZE-200;
        r.x = (G_SIZE - r.w) / 2;
        r.y = (G_SIZE - r.h) / 2;
        SDL_RenderCopy(renderer, snake->gameOverTexture, NULL, &r);
    }

    SDL_RenderPresent(renderer);
}
*/

Segment* Game::getValidFood() {
    Segment* newFood = new Segment(0, 0);
    do {
        newFood->x = rand() % GRID;
        newFood->y = rand() % GRID;
    }
    while (!checkFoodValid(newFood));

    return newFood;
}

bool Game::checkFoodValid(Segment* food) {
    std::vector<Segment *> snakeBody = snake->getBody();
    for(auto segment : snakeBody) {
        if(food->x == segment->x || food->y == segment->y) {
            return false;
        }
    }

    return true;
}
