#include "renderer.hpp"

Renderer::Renderer(const char* title, int posx, int posy, int width,
    int height, bool maximised){

    window   = nullptr;
    renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL2 initialisation failed: " << SDL_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow(title, posx, posy, width, height,
    maximised == true ? SDL_WINDOW_MAXIMIZED : 0);
    if (window == NULL) {
        std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_SetRenderDrawColor(renderer, 122, 164, 82, 255);

    //Load textures
    headTexture     = loadTexture("res/head.png");
    bodyTexture     = loadTexture("res/body.png");
    gameOverTexture = loadTexture("res/gameover.png");
    foodTexture     = loadTexture("res/food.png");
}

Renderer::~Renderer(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

SDL_Texture* Renderer::loadTexture(const char* filename) {
    SDL_Surface * tSurface = IMG_Load(filename);
    if (!tSurface)
        std::cout << "Failed to load image " << filename << ": " << IMG_GetError() << std::endl;
    SDL_Texture * texture  = SDL_CreateTextureFromSurface(renderer, tSurface);
    SDL_FreeSurface(tSurface);
    return texture;
}

void Renderer::render(std::vector<Segment *> snakeBody, Segment* food, bool isGameOn,
    char direction)
{
    SDL_RenderClear(renderer);
    if(isGameOn)
    {
        SDL_Rect r;
        r.w = r.h = C_SIZE;
        r.x = food->x * C_SIZE;
        r.y = food->y * C_SIZE;
        SDL_RenderCopy(renderer, foodTexture, NULL, &r);

        r.x = snakeBody[0]->x * C_SIZE;
        r.y = snakeBody[0]->y * C_SIZE;
        SDL_RenderCopyEx(renderer, headTexture, NULL, &r,
            (direction == DIR_WEST || direction == DIR_EAST) ? 90.0 : 0.0,
            NULL, SDL_FLIP_NONE);

        for (int i = 1; i < (int)snakeBody.size(); i++) {
            r.x = snakeBody[i]->x * C_SIZE;
            r.y = snakeBody[i]->y * C_SIZE;
            SDL_RenderCopy(renderer, bodyTexture, NULL, &r);
        }
    }
    else
    {
        SDL_Rect r;
        r.w = G_SIZE-200;
        r.h = G_SIZE-200;
        r.x = (G_SIZE - r.w) / 2;
        r.y = (G_SIZE - r.h) / 2;
        SDL_RenderCopy(renderer, gameOverTexture, NULL, &r);
    }

    SDL_RenderPresent(renderer);
}
