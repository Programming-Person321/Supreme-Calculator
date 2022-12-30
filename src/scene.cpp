#include "include/scene.hpp"
#include "include/component.hpp"
#include "include/GUI.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Scene::renderObjects(){
    for(Component& c : all){
        render(c, renderer);
    }
    for(Button& b : buttons){
        render(b, renderer);
    }
    for(TextBox& t : texts){
        render(t, renderer);
    }
    for(DropDownMenu& d : menus){
        render(d, renderer);
    }
}

Scene::Scene(){puts("Constructor"); textures.push_back(createBackground()); /*create the background image*/}

void Scene::runGame(){
    for(Button& b : buttons){
        if(b.mouseIntersects()){
            if(b.getPressed()){
                b.setState(2);
            }else{
                b.setState(1);
            }
        }else{
            b.setState(0);
        }
    }
    runVoid(*this);
}

void Scene::mouseChanged(bool b){
    bool keyBool = true;

    for(Button& button : buttons){
        if(button.mouseIntersects()){
            if(button.getPressed() && !b){
                button.pressedFunction(*this, button);
            }
            
            button.setPressed(b);
            keyBool = false;
            continue;
        }
        button.setPressed(false);
    }

    for(TextBox& text : texts){
        if(text.mouseIntersects()){
            if(text.getPressed() && !b){
                text.setKeys(true);
            }
            
            text.setPressed(b);
            keyBool = false;
            continue;
        }
        text.setPressed(false);
        text.setKeys(false);
    }

    for(DropDownMenu& drop : menus){
        if(drop.mouseIntersects()){
            if(drop.getPressed() && !b){
                drop.setKeys(true);
            }
            
            drop.setPressed(b);
            keyBool = false;
            continue;
        }
        drop.setPressed(false);
        drop.setKeys(false);
    }
    
    if(keyBool) mouseVoid(*this);
}

void Scene::keyEvent(SDL_Event& event, bool b){
    // printf("%d\n",  event.key.keysym.sym);
    // if((int)event.key.keysym.sym != 1073741903){

        bool mouseBool = true;

        for(TextBox& t : texts){
            if(t.getKeys() && b){
                int i = (int)event.key.keysym.sym;
                printf("%d\n", i);
                std::string text;
                text+=(char)i;
                if(i != 8) t.addText(text);
                else t.clearText();
                mouseBool = false;
                continue;
            }
        }

        if(mouseBool) clickVoid(*this);
    // }
}

Scene::~Scene(){
    for(SDL_Texture* t : textures){
        SDL_DestroyTexture(t);
    }
}

void Scene::removeScene(){
    for(uint i = 1; i < textures.size(); i++){
        SDL_DestroyTexture(textures[i]);
    }
    textures.erase(textures.begin() + 1, textures.end() + 0);

    printf("After Removing, Texture Size is: %ld\n", textures.size());

    all.clear();
    buttons.clear();
    texts.clear();
    menus.clear();
}

uint8_t Scene::getSceneChange(){
    int s = sceneChange;
    sceneChange = 0;
    return s;
}

void Scene::setSceneChange(uint i){
    sceneChange = i;
    printf("%d\n", sceneChange);
}

void Scene::resize(){ SDL_DestroyTexture(textures[0]); textures[0] = createBackground(); resizeVoid(*this);}

void Scene::loadScene(int loading){
    std::fstream level;
    level.open(  ("res/scenes/scene" + std::to_string(loading) + ".yml")  ,std::ios::in);
    puts(("res/scenes/scene" + std::to_string(loading) + ".yml").c_str());
    if (level.is_open()){
        std::string line;
        while(getline(level, line)){
            if(line.substr(0, 3) == "txt"){
                std::vector<int> spaces;
                int index = 0;
                for(char c : line){
                    if(c == ' ') spaces.push_back(index);
                    index++;
                }
                int x = stoi(line.substr(spaces[0], spaces[1]));
                int y = stoi(line.substr(spaces[1], spaces[2]));
                int s = stoi(line.substr(spaces[2], spaces[3]));
                bool m = (line.substr(spaces[3], spaces[4]).find("1") != std::string::npos);
                std::string text = line.substr(spaces[4] + 1);

                texts.push_back(TextBox("res/fonts/Amaranth-Bold.ttf", s, text.c_str(), x, y));
                textures.push_back(texts[texts.size()-1].getTexture());
                texts[texts.size()-1].setManagement(m);
            }else if(line.substr(0, 3) == "lbl"){
                std::vector<int> spaces;
                int index = 0;
                for(char c : line){
                    if(c == ' ') spaces.push_back(index);
                    index++;
                }
                int x = stoi(line.substr(spaces[0], spaces[1]));
                int y = stoi(line.substr(spaces[1], spaces[2]));
                bool m = (line.substr(spaces[2]).find("1") != std::string::npos);
                // if(line.substr(0, 8) != "lbl:icon"){
                //     textures.push_back(loadFont("res/fonts/Amaranth-Bold.ttf", s, text.c_str(), 255, 255, 255, renderer));
                // }
                all.push_back(Component(textures[textures.size()-1], x, y));
                all[all.size()-1].setManagement(m);
            }else if(line.substr(0, 3) == "drp"){
                std::vector<int> spaces;
                int index = 0;
                for(char c : line){
                    if(c == ' ') spaces.push_back(index);
                    index++;
                }

                int x = stoi(line.substr(spaces[0], spaces[1]));
                int y = stoi(line.substr(spaces[1], spaces[2]));
                int s = stoi(line.substr(spaces[2], spaces[3]));
                bool m = (line.substr(spaces[3], spaces[4]).find("1") != std::string::npos);
                std::string options = line.substr(spaces[4]).c_str();

                std::vector<std::string> list;
                index = 0;
                spaces.clear();
                for(char c : options){
                    if(c == '/') {spaces.push_back(index); printf("%d\n", index);} 
                    index++;
                }

                for(uint i = 0; i < spaces.size()-1; i++){
                    std::string item = options.substr(spaces[i]+1, spaces[i+1]-spaces[i]-1);
                    list.push_back(item);
                }

                puts("adding");
                menus.push_back(DropDownMenu(x, y, s, "res/fonts/Amaranth-Bold.ttf", list));
                puts("adding stage 2");
                textures.push_back(menus[menus.size()-1].getTexture());
                menus[menus.size()-1].setManagement(m);
            }else if(line.substr(0, 3) == "btn"){
                std::vector<int> spaces;
                int index = 0;
                for(char c : line){
                    if(c == ' ') spaces.push_back(index);
                    index++;
                }

                int x = stoi(line.substr(spaces[0], spaces[1]));
                int y = stoi(line.substr(spaces[1], spaces[2]));
                bool m = (line.substr(spaces[2], spaces[3]).find("1") != std::string::npos);
                std::string code = line.substr(spaces[3]);
                printf("Code is:%s\n", code.c_str());

                // if(line.substr(0, 8) != "btn:icon"){
                //     puts("no icons");
                //     textures.push_back(loadFont("res/fonts/Amaranth-Bold.ttf", s,  text.c_str(), 255, 255, 0, renderer));
                //     textures.push_back(loadFont("res/fonts/Amaranth-Bold.ttf", s,  text.c_str(), 255, 0, 255, renderer));
                //     textures.push_back(loadFont("res/fonts/Amaranth-Bold.ttf", s,  text.c_str(), 0, 255, 255, renderer));
                // }

                if(code.find("LOAD") != std::string::npos) {buttons.push_back(Button(textures[textures.size()-3], textures[textures.size()-2], textures[textures.size()-1], x, y, load, code)); buttons[buttons.size()-1].setManagement(m);}
           else if(code.find("ADD") != std::string::npos) {buttons.push_back(Button(textures[textures.size()-3], textures[textures.size()-2], textures[textures.size()-1], x, y, add, code)); buttons[buttons.size()-1].setManagement(m);}
           else if(code.find("APPEND") != std::string::npos) {buttons.push_back(Button(textures[textures.size()-3], textures[textures.size()-2], textures[textures.size()-1], x, y, appendText, code)); buttons[buttons.size()-1].setManagement(m);}
           else if(code.find("CALCULATE") != std::string::npos) {buttons.push_back(Button(textures[textures.size()-3], textures[textures.size()-2], textures[textures.size()-1], x, y, calculate, code)); buttons[buttons.size()-1].setManagement(m);}
           else if(code.find("NONE") != std::string::npos) {buttons.push_back(Button(textures[textures.size()-3], textures[textures.size()-2], textures[textures.size()-1], x, y, noneButton, code)); buttons[buttons.size()-1].setManagement(m);}
           else{puts("No Known Functionality for the desired button");}
                
            }else if(line.substr(0, 3) == "img"){
                textures.push_back(loadImage(line.substr(5).c_str(), renderer));
            }else if(line.substr(0, 3) == "tlb"){
                std::vector<int> spaces;
                int index = 0;
                for(char c : line){
                    if(c == ' ') spaces.push_back(index);
                    index++;
                }

                int s = std::stoi(line.substr(spaces[1], spaces[2]));
                std::string text = line.substr(spaces[2]);

                std::string options = line.substr(spaces[0], spaces[1]);

                std::vector<std::string> list;
                index = 0;
                spaces.clear();
                for(char c : options){
                    if(c == '/') {spaces.push_back(index); printf("%d\n", index);} 
                    index++;
                }

                for(uint i = 0; i < spaces.size()-1; i++){
                    std::string item = options.substr(spaces[i]+1, spaces[i+1]-spaces[i]-1);
                    list.push_back(item);
                }

                int r = std::stoi(list[0]);
                int g = std::stoi(list[1]);
                int b = std::stoi(list[2]);

                TTF_Font* font = TTF_OpenFont("res/fonts/Amaranth-Bold.ttf", s);
                SDL_Color colour;
                colour = {255, 255, 255};
                SDL_Surface* message;
                message = TTF_RenderText_Blended(font, text.c_str(), colour);

                SDL_Rect size = {0,0,message->w,message->h};
                SDL_Surface *back = SDL_CreateRGBSurface(0, size.w, size.h, 32, 0, 0, 0, 0);
                SDL_FillRect(back, &size, SDL_MapRGB(back->format, r, g, b));

                SDL_BlitSurface(message, &message->clip_rect, back, &back->clip_rect);

                
                textures.push_back(loadTextureFromSurface(back, renderer));

                SDL_FreeSurface(back);
                SDL_FreeSurface(message);
                TTF_CloseFont(font);

 

            }else if(line.substr(0, 3) == "sem"){
                std::vector<int> spaces;
                int index = 0;
                for(char c : line){if(c == ' ') spaces.push_back(index); index++;}

                std::string code = line.substr(spaces[0]);
                if(line.find("RMBUTTONS") != std::string::npos) {mouseVoid = removeButtons; mouseInstructions = code;}
                if(line.find("RESIZE") != std::string::npos) {mouseVoid = center;}
                if(line.find("NONE") != std::string::npos) {mouseVoid = none;}
                if(line.find("BACK") != std::string::npos) {mouseVoid = background;}
                if(line.find("HOMESCREEN") != std::string::npos) {mouseVoid = homescreen;}
            }else if(line.substr(0, 3) == "ser"){
                std::vector<int> spaces;
                int index = 0;
                for(char c : line){if(c == ' ') spaces.push_back(index); index++;}

                std::string code = line.substr(spaces[0]);
                if(line.find("RMBUTTONS") != std::string::npos) {resizeVoid = removeButtons; mouseInstructions = code;}
                if(line.find("RESIZE") != std::string::npos) {resizeVoid = center;}
                if(line.find("NONE") != std::string::npos) {resizeVoid = none;}
                if(line.find("BACK") != std::string::npos) {resizeVoid = background;}
                if(line.find("HOMESCREEN") != std::string::npos) {resizeVoid = homescreen;}
            }else if(line.substr(0, 3) == "sec"){
                std::vector<int> spaces;
                int index = 0;
                for(char c : line){if(c == ' ') spaces.push_back(index); index++;}

                std::string code = line.substr(spaces[0]);
                if(line.find("RMBUTTONS") != std::string::npos) {clickVoid = removeButtons; mouseInstructions = code;}
                if(line.find("RESIZE") != std::string::npos) {clickVoid = center;}
                if(line.find("NONE") != std::string::npos) {clickVoid = none;}
                if(line.find("BACK") != std::string::npos) {clickVoid = background;}
                if(line.find("HOMESCREEN") != std::string::npos) {clickVoid = homescreen;}
            }else if(line.substr(0, 3) == "seg"){
                std::vector<int> spaces;
                int index = 0;
                for(char c : line){if(c == ' ') spaces.push_back(index); index++;}

                std::string code = line.substr(spaces[0]);
                if(line.find("RMBUTTONS") != std::string::npos) {runVoid = removeButtons; mouseInstructions = code;}
                if(line.find("RESIZE") != std::string::npos) {runVoid = center;}
                if(line.find("NONE") != std::string::npos) {runVoid = none;}
                if(line.find("BACK") != std::string::npos) {runVoid = background;}
                if(line.find("HOMESCREEN") != std::string::npos) {runVoid = homescreen;}
            }
        }
        level.close();
        resizeVoid(*this);
    }else{
        puts("Error Reading File");
    }

}

std::string Scene::getMouseInstructions(){
    return mouseInstructions;
}

void Scene::buttonsClear(int i){
    if(buttons.size() > 2) buttons.erase(buttons.begin() + buttons.size()-i, buttons.end());
}

//getters and setters

std::vector<Component>& Scene::getAll(){
    return all;
}
std::vector<Button>& Scene::getButtons(){
    return buttons;
}
std::vector<TextBox>& Scene::getTexts(){
    return texts;
}
std::vector<DropDownMenu>& Scene::getMenus(){
    return menus;
}
std::vector<SDL_Texture*>& Scene::getTextures(){
    return textures;
}