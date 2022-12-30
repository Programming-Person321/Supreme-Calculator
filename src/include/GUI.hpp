#ifndef GUI_HPP
#define GUI_HPP
#include "scene.hpp"
#include "window.hpp"

///////////VERY IMPORTANT///////////////////////////

class Scene;//forward declaration of Scene - so that it knows that Scene is
class Button;

////////////////////////////////////////////////////

void load(Scene& scene, Button& b);
void add(Scene& scene, Button& b);
void noneButton(Scene& scene, Button& b);
void createAccount(Scene& scene, Button& b);
void login(Scene& scene, Button& b);
void appendText(Scene& scene, Button& b);
void calculate(Scene& scene, Button& b);

void removeButtons(Scene& scene);
void center(Scene& scene);
void homescreen(Scene& scene);
void none(Scene& scene);
void background(Scene& scene);

#endif