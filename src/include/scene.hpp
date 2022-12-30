#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>
#include "component.hpp"
#include "window.hpp"
#include "button.hpp"
#include "textBox.hpp"
#include "dropDownMenu.hpp"

class Button;

class Scene{
private:
    std::vector<Component> all;
    std::vector<Button> buttons;
    std::vector<TextBox> texts;
    std::vector<DropDownMenu> menus;

    std::vector<SDL_Texture*> textures;
    
    uint8_t sceneChange = 0;

    std::string mouseInstructions;

    void(* resizeVoid)(Scene&);
    void(* clickVoid)(Scene&);
    void(* mouseVoid)(Scene&);
    void(* runVoid)(Scene&);

public:
    void resetVoids();
    void buttonsClear(int index);

    std::string getMouseInstructions();

    virtual void runGame();
    void mouseChanged(bool b);
    virtual void keyEvent(SDL_Event& event, bool b);//.key.keysym.sym
    virtual ~Scene();

    virtual void resize();

    void renderObjects(); 

    uint8_t getSceneChange();
    void setSceneChange(uint i);

    void loadScene(int loading);
    void removeScene();

    //getters and setters
    std::vector<Component>& getAll();
    std::vector<Button>& getButtons();
    std::vector<TextBox>& getTexts();
    std::vector<DropDownMenu>& getMenus();
    std::vector<SDL_Texture*>& getTextures();
    Scene();
};

#endif