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
    Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255); // TODO
    const std::string toHexString() const;
    const sf::Color getSFColor() const;

    sf::Color getsf(); // return SF::COLOR

    static Color fromHSV(const uint8_t h, const uint8_t s, const uint8_t v, const uint8_t a = 255); // TODO

    Color lighten(int16_t value) const;

    Color invert() const;

    uint8_t getR () const { return r; };
    uint8_t getG () const { return g; };
    uint8_t getB () const { return b; };
    uint8_t getA () const { return a; };
private:
    uint8_t r; // red
    uint8_t g; // green
    uint8_t b; // blue
    uint8_t a; // alpha
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

private:
    sf::RenderWindow &window;
    bool active;
};
}   // namespace graphics
