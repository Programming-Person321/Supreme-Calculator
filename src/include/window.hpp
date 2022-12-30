#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SDL2/SDL.h>
#include "component.hpp"

//global variables and functions
extern SDL_Renderer* renderer;
extern float delta;
SDL_Texture * loadImage(const char* path, SDL_Renderer* ren);
SDL_Texture * loadFont(const char* path, uint size, const char* text, uint8_t r, uint8_t g, uint8_t b, SDL_Renderer* ren);
SDL_Texture * loadTextureFromSurface(SDL_Surface* s, SDL_Renderer* ren);
void render(Component& c, SDL_Renderer* ren);

class Window{
    SDL_Window* win;
public:
    Window(const char* title, int w, int h);
    void clean();
    int getRefreshRate();
};

#endif