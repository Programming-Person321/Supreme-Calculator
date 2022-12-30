#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "SDL2/SDL.h"

struct Vector{
    int x, y;
};

struct Vector3{
    int x, y, z;
};

SDL_Texture* createBackground();

#endif