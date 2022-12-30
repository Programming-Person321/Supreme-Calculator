#include "include/component.hpp"

Vector Component::getPos(){
    return pos;
}

SDL_Texture* Component::getTexture(){
    return t;
}

void Component::setPos(int x, int y){
    pos = {x, y};
}

Component::Component(SDL_Texture* tex, int _x, int _y):t(tex){
    pos = {_x, _y};
    originalPos = pos;
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    dimensions = {w, h};
}

Vector Component::getDim(){
    return dimensions;
}

void Component::setTexture(SDL_Texture* tex){
    t = tex;
}

bool Component::mouseIntersects(){
    int x, y;
    SDL_GetMouseState(&x, &y);

    if(x > getPos().x && x < getPos().x + getDim().x && y > getPos().y && y < getPos().y + getDim().y){
        return true;
    }

    return false;
}

Component::Component(){}

void Component::setDim(int x, int y){
    dimensions = {x, y};
}

bool Component::getManagement(){
    return manageGUI;
}

void Component::setManagement(bool b){
    manageGUI = b;
}

Vector Component::getOriginalPos(){
    return originalPos;
}