#include "game.hpp"

Game * game = nullptr;

int main(int argc, char * argv[]) {
    srand(time(NULL));
    const int frameRate  = 5;
    const int frameDelay = 1000 / frameRate;

    Uint32 frameTime;
    int frameElapsedTime;

    game = new Game();
    game->init("Snake", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, G_SIZE, G_SIZE, false);
    while (game->isRunning()) {
        frameTime = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameElapsedTime = SDL_GetTicks() - frameTime;
        if (frameDelay > frameElapsedTime)
            SDL_Delay(frameDelay - frameElapsedTime);
    }
    game->clean();
    return 0;
}
