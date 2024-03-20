#pragma once
#include "SFML/Graphics.hpp"
#include "animation.h"
#include "color.h"
#include "keyboard/keyboard.h"
#include "sprite.h"
#include "text.h"
#include <iostream>
#include <map>

namespace graphics {
class Text;
class Color;

struct Rectangle {
    float x;
    float y;
    float w;
    float h;
    Color color = Color("#ffffffff");
    float stroke = 0;
    Color stroke_color = Color("#000000ff");
};

class Renderer {
public:
    // constructor
    Renderer(sf::RenderWindow &window);

    void display();
    void clear();

    void drawSprite(int x, int y, const std::string &sprite_id);

    void drawRec(const Rectangle &rectangle);

    void drawText(int x, int y, const std::string &line);

    void draw(const Text &text, int x, int y);

    void draw(const Sprite &sprite, int x, int y);

    void close() {
        window.close();
    }

    bool isActive() {
        return active;
    }

    void open() {
        active = true;
    }

private:
    sf::RenderWindow &window;
    bool active;
};
}   // namespace graphics
