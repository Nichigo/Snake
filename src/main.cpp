#include <SDL2/SDL.h>
#include "game.hpp"
#include "renderer.hpp"

int main(int argc, char * argv[]) {
    Game * game = nullptr;
    srand(time(NULL));
    const int frameRate  = 8;
    const int frameDelay = 1000 / frameRate;

    Uint32 frameTime;
    int frameElapsedTime;

    game = new Game();
    Renderer *renderer =  new Renderer("Snek", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, G_SIZE, G_SIZE, false);
    while (game->isRunning()) {
        frameTime = SDL_GetTicks();

        game->handleEvents();
        game->update();
        renderer->render(game->snake->getBody(), game->food,
            game->snake->isAlive(), game->snake->getDirection());

        frameElapsedTime = SDL_GetTicks() - frameTime;
        if (frameDelay > frameElapsedTime)
            SDL_Delay(frameDelay - frameElapsedTime);
    }

    delete game;
    return 0;
}
