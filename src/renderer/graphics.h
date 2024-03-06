#pragma once
#include "SFML/Graphics.hpp"
#include "keyboard/keyboard.h"
#include "text.h"
#include <iostream>
#include <map>

namespace graphics {
class Color {
public:
    Color();
    Color(const std::string &hex_str);
    Color(const sf::Color &color);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    [[nodiscard]] sf::Color getSFColor() const;

    [[nodiscard]] uint8_t getR() const {
        return r;
    };

    [[nodiscard]] uint8_t getG() const {
        return g;
    };

    [[nodiscard]] uint8_t getB() const {
        return b;
    };

    [[nodiscard]] uint8_t getA() const {
        return a;
    };

private:
    uint8_t r;   // red
    uint8_t g;   // green
    uint8_t b;   // blue
    uint8_t a;   // alpha
};

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

    void draw(const Text& text, int x, int y);

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
