#include "game.hpp"

Game::Game(const char* title, int posx, int posy, int width,
    int height, bool maximised) {
    window   = nullptr;
    renderer = nullptr;
    running  = false;
    snake    = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL2 initialisation failed: " << SDL_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow(title, posx, posy, width, height,
      maximised == true ? SDL_WINDOW_MAXIMIZED : NULL);
    if (window == NULL) {
        std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, NULL);
    if (renderer == NULL) {
        std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 122, 164, 82, 255);
    running = true;
    snake = new Snake(GRID / 2, GRID / 2, rand() % 4, renderer);
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    delete snake;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    snake->setDirection(Snake::NORTH);
                    break;
                case SDLK_DOWN:
                    snake->setDirection(Snake::SOUTH);
                    break;
                case SDLK_LEFT:
                    snake->setDirection(Snake::WEST);
                    break;
                case SDLK_RIGHT:
                    snake->setDirection(Snake::EAST);
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
        snake->checkAndEatFood();
        snake->move();
    }
}

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

void Game::clean() {

}
