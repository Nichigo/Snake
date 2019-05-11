#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "global_constants.hpp"
#include "segment.hpp"

class Renderer {

public:
    Renderer(const char * title, int posx, int posy, int width,
      int height, bool maximised);
    ~Renderer();
    void render(std::vector<Segment *> snakeBody, Segment* food, bool isGameOn,
        char direction);

private:
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * headTexture;
    SDL_Texture * bodyTexture;
    SDL_Texture * foodTexture;
    SDL_Texture * gameOverTexture;
    SDL_Texture * loadTexture(const char * filename);
};

#endif //RENDERER_HPP_INCLUDED
