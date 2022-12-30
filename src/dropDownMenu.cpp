#include "include/dropDownMenu.hpp"

#include <SDL2/SDL_ttf.h>

DropDownMenu::DropDownMenu(int x, int y, int s, const char * path, std::vector<std::string> initialItems) : size(s), fontPath(path){
    items = initialItems;
    setPos(x, y);
    originalPos = pos;
    render();
}

void DropDownMenu::render(){
    TTF_Font* font = TTF_OpenFont(fontPath, size);
    SDL_Color colour;
    std::vector<SDL_Surface*> messages;
    int w = 0;
    int h = 0;
    for(uint i = 0; i < items.size(); i++){
        if(keys && i == selectedItem) colour = {255, 0, 0};
        else colour = {0, 0, 0};
        messages.push_back(TTF_RenderText_Blended(font, items[i].c_str(), colour));
        if(messages[i]->w > w) w = messages[i]->w;
        h += messages[i]->h;
        itemSize = {w, messages[i]->h};
    }

    if(keys) setDim(w, h);
    else setDim(w, messages[selectedItem]->h);

    SDL_Rect size = {0,0,dimensions.x,dimensions.y};
    SDL_Surface *back = SDL_CreateRGBSurface(0, size.w, size.h, 32, 0, 0, 0, 0);
    SDL_FillRect(back, &size, SDL_MapRGB(back->format, 255, 255, 255));

    if(keys){
        int currentY = 0;
        for(SDL_Surface* s: messages){
            SDL_Rect dstRect = back->clip_rect;
            dstRect.y = currentY;
            SDL_BlitSurface(s, &s->clip_rect, back, &dstRect);
            currentY += dstRect.h;
            SDL_FreeSurface(s);
        }
    }else{
        SDL_BlitSurface(messages[selectedItem], &messages[selectedItem]->clip_rect, back, &back->clip_rect);
    }

    SDL_DestroyTexture(getTexture());
    setTexture(loadTextureFromSurface(back, renderer));
    

    SDL_FreeSurface(back); 
    TTF_CloseFont(font);
}

//mouse functions
void DropDownMenu::setPressed(bool b){
    pressed = b;
}

bool DropDownMenu::getPressed(){
    return pressed;
}

//key functions
void DropDownMenu::setKeys(bool b){
    if(keys == true){
        int x, y;
        SDL_GetMouseState(&x, &y);

        for(int i = 0; i < (int) items.size(); i++){

            if(x > getPos().x && x < getPos().x + getDim().x && y > getPos().y+(itemSize.y*i) && y < getPos().y+((itemSize.y)*(i+1))){
                selectedItem = i;
            } 
        }
    }
    keys = b;
    render();
}

bool DropDownMenu::getKeys(){
    return keys;
}

int DropDownMenu::getSelectedItem(){
    return selectedItem;
}