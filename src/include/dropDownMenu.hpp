#ifndef DROPDOWNMENU_HPP
#define DROPDOWNMENU_HPP

#include "component.hpp"
#include "window.hpp"
#include <vector>
#include <string>

class DropDownMenu : public Component{
private:
    std::vector<std::string> items;
    Vector itemSize = {10, 10};
    uint selectedItem = 0;
    int size;
    const char* fontPath;
    bool pressed = false;
    bool keys = false;

    void render();
public:
    DropDownMenu(int x, int y, int s, const char * path, std::vector<std::string> initialItems);

    void setPressed(bool b);
    bool getPressed();
    void setKeys(bool b);
    bool getKeys();
    int getSelectedItem();
};

#endif