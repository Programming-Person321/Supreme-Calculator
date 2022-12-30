#include "include/button.hpp"
#include "include/component.hpp"
#include "include/scene.hpp"

Button::Button(SDL_Texture* tex, SDL_Texture* h, SDL_Texture* p, int _x, int _y, void(*press)(Scene&, Button&), std::string code  ) : instructions(code), pressedFunction(press){
    pos = {_x, _y};
    originalPos = {_x, _y};
    int wi, hi;
    SDL_QueryTexture(tex, NULL, NULL, &wi, &hi);
    dimensions = {wi, hi};

    t = tex;

    normalTexture = tex;
    hoverTexture = h;
    pressedTexture = p;
}

void Button::setState(uint8_t state){
    switch(state){
        case 0:
            t = normalTexture;
        break;
        case 1:
            t = hoverTexture;
        break;
        case 2:
            t = pressedTexture;
        break;
    }
}

void Button::setPressed(bool b){
    pressed = b;
}

bool Button::getPressed(){
    return pressed;
}
