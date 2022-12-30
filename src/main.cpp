//new
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "include/window.hpp"
#include "include/component.hpp"
#include "include/scene.hpp"
#include "include/utilities.hpp"
#include "include/sound.hpp"

int main(int argc, char* args[]){

    puts("\nStarting Program:\n");
    
    if(SDL_Init(SDL_INIT_VIDEO) > 0) puts(SDL_GetError());
    if(!(IMG_Init(IMG_INIT_PNG))) puts(SDL_GetError());
    if((TTF_Init() == -1)) puts(SDL_GetError());
    soundInit();

    Window window("Supreme Calculator", 375, 667);

    std::vector<Scene*> scenes;

    scenes.push_back(new Scene());
    scenes[0]->loadScene(1);

    scenes[0]->resize();

    bool running = true;
    SDL_Event event;

    int startOfLastFrame = SDL_GetTicks();

    while(running){
        int startTime = SDL_GetTicks();
        delta = (startTime - startOfLastFrame) * 0.001f;
        startOfLastFrame = startTime;

        SDL_RenderClear(renderer);

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                break;
                case SDL_MOUSEBUTTONUP:
                    scenes[0]->mouseChanged(false);
                break;
                case SDL_MOUSEBUTTONDOWN:
                    scenes[0]->mouseChanged(true);
                break;
                case SDL_KEYDOWN:
                    scenes[0]->keyEvent(event, true);
                break;
                case SDL_KEYUP:
                    scenes[0]->keyEvent(event, false);
                break;
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                        scenes[0]->resize();
                        puts("Resizing................................................................................");
                        
                    }
                break;
            }
        }

            scenes[0]->runGame();

            uint8_t s = scenes[0]->getSceneChange();

            if(s != 0){
                printf("Scene to Change: %d\n", s);
                
                // scenes.push_back(new Scene());
                scenes[0]->removeScene();
                scenes[0]->loadScene(s);

                // delete scenes[0];
                // scenes.erase(scenes.begin() + 0);
            }
        
        scenes[0]->renderObjects();

        SDL_RenderPresent(renderer);

        int totalRenderingTime = SDL_GetTicks() - startTime;
        if(totalRenderingTime < 1000 / window.getRefreshRate()) SDL_Delay((1000/window.getRefreshRate()) - totalRenderingTime);
    }

    for(Scene* s : scenes){
        delete s;
    }
    window.clean();
    SDL_Quit();
    return 0;
}
