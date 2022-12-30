#include "include/scene.hpp"
#include "include/GUI.hpp"
#include <iostream>
#include <fstream>
#include <string>

void load(Scene& scene, Button& b){
    int sceneToShow = stoi(b.getInstructions().substr(7, 1));
    scene.setSceneChange(sceneToShow);
    puts("Pressed");
}

void add(Scene& scene, Button& b){
    int sceneToShow = stoi(b.getInstructions().substr(6, 2));
    scene.loadScene(sceneToShow);
}

void noneButton(Scene& scene, Button& b){}

void removeButtons(Scene& scene){
    int buttonsToRemove = stoi(scene.getMouseInstructions().substr(12, 2));
    scene.buttonsClear(buttonsToRemove);
}

void appendText(Scene& scene, Button& b){
    std::string text = b.getInstructions().substr(9, b.getInstructions().length()-11);
    printf("%ld\n",b.getInstructions().length()-11);
    printf("%s\n", text.c_str());
    scene.getTexts()[0].addText(text);
}

void calculate(Scene& scene, Button& b){
    puts("Calculating...");
}

void none(Scene& scene){}

void homescreen(Scene& scene){
    puts("Homescreen");
}

void center(Scene& scene){
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    for(Component& c : scene.getAll()){
    if(c.getManagement())
        c.setPos(((width/2)-(c.getDim().x/2)) + c.getOriginalPos().x, (height/2)-(c.getDim().y/2) + c.getOriginalPos().y);
    }
    for(Button& c : scene.getButtons()){
    if(c.getManagement())
        c.setPos(((width/2)-(c.getDim().x/2)) + c.getOriginalPos().x, (height/2)-(c.getDim().y/2) + c.getOriginalPos().y);
    }
    for(TextBox& c : scene.getTexts()){
    if(c.getManagement()){
            c.setDim(width, c.getDim().y);
            printf("1Dimensions are: %d, %d", c.getDim().x, c.getDim().y);
            c.renderText();
            printf("2Dimensions are: %d, %d", c.getDim().x, c.getDim().y);
        }
    }
    for(DropDownMenu& c : scene.getMenus()){
    if(c.getManagement())
        c.setPos(((width/2)-(c.getDim().x/2)) + c.getOriginalPos().x, (height/2)-(c.getDim().y/2) + c.getOriginalPos().y);
    }
}

void background(Scene& scene){
    static float movement = 0;
    movement += delta;
    while(movement > 0.05){
        movement -= 0.05f;
        int width, height;
        SDL_GetRendererOutputSize(renderer, &width, &height);
        SDL_Texture* image = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
        SDL_SetRenderTarget(renderer, image);
        SDL_Rect src = {0, 0, width, height};
        SDL_Rect dst = {-1, -1, width, height};

        SDL_RenderCopy(renderer, scene.getTextures()[0], &src, &dst);
        dst.x = width-1;
        dst.y = 0;
        SDL_RenderCopy(renderer, scene.getTextures()[0], &src, &dst);
        dst.x = 0;
        dst.y = height-1;
        SDL_RenderCopy(renderer, scene.getTextures()[0], &src, &dst);

        SDL_SetRenderTarget(renderer, NULL);

        SDL_DestroyTexture(scene.getTextures()[0]);
        scene.getTextures()[0] = image;
    }

    SDL_RenderCopy(renderer, scene.getTextures()[0], NULL, NULL);
    
}