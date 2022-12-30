#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "component.hpp"
#include "scene.hpp"
#include <string>

class Scene;

class Button : public Component{
private:
    SDL_Texture* normalTexture;
    SDL_Texture* hoverTexture;
    SDL_Texture* pressedTexture;

    bool pressed = false;

    std::string instructions;
    
public:
void(*pressedFunction)(Scene&, Button&);
    Button(SDL_Texture* tex, SDL_Texture* h, SDL_Texture* p, int _x, int _y, void(*press)(Scene&, Button&), std::string code);
    void setState(uint8_t state);

    void setPressed(bool b);
    bool getPressed();

    

    std::string getInstructions() const{
        return instructions;
    }
};

#endif