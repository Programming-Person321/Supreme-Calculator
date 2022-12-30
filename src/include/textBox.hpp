#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "component.hpp"
#include "window.hpp"
#include <string>

class TextBox : public Component{
private:
    std::string text;
    bool pressed = false;
    bool keys = false;
    
    void renderText();
    const char* fontPath;
    int size;
public:
    void addText(char);
    void clearText();
    std::string getText();

    void setPressed(bool b);
    bool getPressed();
    void setKeys(bool b);
    bool getKeys();

    TextBox(const char*, int, const char*, int, int);
};

#endif