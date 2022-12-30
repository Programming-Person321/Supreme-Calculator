#include "include/window.hpp"
#include "include/component.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Renderer* renderer = nullptr;
float delta = 0;

SDL_Texture * loadImage(const char* path, SDL_Renderer* ren){
    SDL_Texture* t = NULL;
    t = IMG_LoadTexture(ren, path);

    if(t == NULL) puts(SDL_GetError());

    return t;
}

SDL_Texture* loadFont(const char* path, uint size, const char* text, uint8_t r, uint8_t g, uint8_t b, SDL_Renderer* ren) {
    TTF_Font* font = NULL;
    font = TTF_OpenFont(path, size);
    if(font == NULL) puts("NULL");
    SDL_Color colour = {r, g, b};
    SDL_Surface* s = NULL;
    s = TTF_RenderText_Blended(font, text, colour);
    if(s == NULL) puts("S = NULL");
    SDL_Texture* message = NULL;
    message = SDL_CreateTextureFromSurface(ren, s);
    if(message == NULL) puts(SDL_GetError());
    SDL_FreeSurface(s);
    TTF_CloseFont(font);
    return message;
}

SDL_Texture* loadTextureFromSurface(SDL_Surface* s, SDL_Renderer* ren){
    SDL_Texture* t =  SDL_CreateTextureFromSurface(ren, s);
    if(t == NULL) puts("no Texture was Created --------------------------------------------");
    return t;
}

void render(Component& c, SDL_Renderer* ren){
    // int w, h;
    // SDL_QueryTexture(c->getTexture(), NULL, NULL, &w, &h);
    SDL_Rect src = {0, 0, c.getDim().x, c.getDim().y};
    SDL_Rect dst = {c.getPos().x, c.getPos().y, c.getDim().x, c.getDim().y};

    SDL_RenderCopy(ren, c.getTexture(), &src, &dst);
}


Window::Window(const char* title, int w, int h) {
    win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface * icon = IMG_Load("res/images/icon.png");
    SDL_SetWindowIcon(win, icon);
    SDL_FreeSurface(icon);

    // SDL_SetRenderDrawColor(renderer, 255, 0, 255, 1);
}

void Window::clean(){
    SDL_DestroyWindow(win);
}

int Window::getRefreshRate(){
    int displayIndex = SDL_GetWindowDisplayIndex(win);

    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    
    return mode.refresh_rate;
}