#pragma once
#include "SFML/Graphics.hpp"
#include "keyboard/keyboard.h"
#include <iostream>
#include <map>

namespace graphics {
class Color {
public:
    Color(const std::string &hex_str);
    Color(const uint32_t &hex);
    Color(const sf::Color &color);
    const std::string toHexString() const;
    const sf::Color getSFColor() const;

private:
    sf::Color sfcolor;
};

struct Rectangle {
    float x;
    float y;
    float w;
    float h;
    Color color = 0xffffffff;   // this type is temporary! later I will write a wholesome Color class.
    float stroke = 0;
    Color stroke_color = 0x000000ff;
};

class Renderer {
public:
    // constructor
    Renderer(sf::RenderWindow &window);

    void display();
    void updateState(uint64_t deltatime);
    void clear();

    void drawSprite(int x, int y, const std::string &sprite_id);

    void drawRec(const Rectangle &rectangle);

    void drawText(int x, int y, const std::string &line);

    void close() {
        window.close();
    }

    bool isActive() {
        return active;
    }

    void open () {
        active = true;
    }

    uint64_t getDeltaTime() {
        return m_delta_time;
    }

private:
    uint64_t m_delta_time;
    sf::RenderWindow &window;
    bool active;
};
}   // namespace graphics
