#include "include/textBox.hpp"

#include <SDL2/SDL_ttf.h>

//Constructor
TextBox::TextBox(const char* _fontPath, int _size, const char* _text, int x, int y) : text(_text), fontPath(_fontPath), size(_size){
    setPos(x, y);
    originalPos = pos;
    renderText();
}

//rendering Text
void TextBox::renderText(){

    TTF_Font* font = TTF_OpenFont(fontPath, size);
    SDL_Color colour;
    if(getKeys()) colour = {255, 0, 0};
    else colour = {0, 0, 0};
    SDL_Surface* message;
    if (text != "") message = TTF_RenderText_Blended(font, text.c_str(), colour);
    else message = TTF_RenderText_Blended(font, " ", colour);
    setDim(dimensions.x, message->h);

    SDL_Rect size = {0,0,dimensions.x,dimensions.y};
    SDL_Surface *back = SDL_CreateRGBSurface(0, size.w, size.h, 32, 0, 0, 0, 0);
    SDL_FillRect(back, &size, SDL_MapRGB(back->format, 255, 255, 255));

    SDL_BlitSurface(message, &message->clip_rect, back, &back->clip_rect);

    SDL_DestroyTexture(getTexture());
    setTexture(loadTextureFromSurface(back, renderer));

    SDL_FreeSurface(back);
    SDL_FreeSurface(message);
    TTF_CloseFont(font);
}

//text functions
void TextBox::addText(std::string s){
    puts("Adding Text");
    text = text+s;
    printf("Text now is: %s\n", text.c_str());
    renderText();
}

std::string TextBox::getText(){
    puts("Getting Text");
    return text;
}

void TextBox::clearText(){
    puts("Clearing Text");
    text = "";
    renderText();
}

//mouse functions
void TextBox::setPressed(bool b){
    pressed = b;
}

bool TextBox::getPressed(){
    return pressed;
}

//key functions
void TextBox::setKeys(bool b){
    puts("Setting Keys");
    keys = b;
    renderText();
}

bool TextBox::getKeys(){
    puts("Getting Keys");
    return keys;
}