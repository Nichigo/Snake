#include "game.hpp"

int main(int argc, char * argv[]) {
    Game * game = nullptr;
    srand(time(NULL));
    const int frameRate  = 10;
    const int frameDelay = 1000 / frameRate;

    Uint32 frameTime;
    int frameElapsedTime;

    game = new Game("Snake", SDL_WINDOWPOS_CENTERED,
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

    delete game;
    return 0;
}
