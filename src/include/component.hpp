#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include <SDL2/SDL.h>
#include "utilities.hpp"

class Component{
protected:
    SDL_Texture* t;
    Vector pos;
    Vector originalPos;
    Vector dimensions = {100, 100};
    bool manageGUI = false;
public:
    Vector getPos();
    Vector getOriginalPos();
    Vector getDim();
    SDL_Texture* getTexture();
    void setTexture(SDL_Texture* t);
    void setPos(int x, int y);
    void setDim(int x, int y);
    bool mouseIntersects();
    bool getManagement();
    void setManagement(bool b);
    Component(SDL_Texture* tex, int _x, int _y);
    Component();
};

#endif