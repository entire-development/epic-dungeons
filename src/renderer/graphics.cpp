#include "graphics.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace graphics;

Renderer::Renderer(sf::RenderWindow &window) : window(window) {}

void Renderer::clear() {
    window.clear();
}

void Renderer::display() {
    window.display();
}

void Renderer::drawSprite(int x, int y, const std::string &sprite_id) {
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color(100, 250, 50));
    window.draw(shape);
}

void Renderer::drawText(int x, int y, const std::string &line) {
    sf::Font font;
    if (!font.loadFromFile(cfg::FONT_PATH)) {
        std::cerr << "Font not found!" << std::endl;
        return;
    }
    sf::Text text;
    text.setFont(font);
    text.setString(line);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
    window.draw(text);
}

void Renderer::drawRec(const Rectangle &rectangle) {
    sf::RectangleShape new_rectangle;
    new_rectangle.setSize(sf::Vector2f(rectangle.w, rectangle.h));
    new_rectangle.setFillColor(rectangle.color.getSFColor());
    new_rectangle.setOutlineColor(rectangle.stroke_color.getSFColor());
    new_rectangle.setOutlineThickness(5);
    new_rectangle.setPosition(rectangle.x, rectangle.y);
    window.draw(new_rectangle);
}

void Renderer::draw(const Text& text, int x, int y) {
    sf::Text set_text = text.toSF();
    set_text.setPosition(x, y);
    window.draw(set_text);
}

graphics::Color::Color(const std::string &hex_str) {
    assert(hex_str[0] == '#' && (hex_str.size() == 7 || hex_str.size() == 9)
           && std::all_of(hex_str.begin() + 1, hex_str.end(), isxdigit));

    std::stringstream ss;
    ss << hex_str.substr(1);

    uint32_t hex;
    ss >> std::hex >> hex;

    if (hex_str.size() == 7) {
        hex <<= 8;
        hex += 0xFF;
    }

    r = (hex & 0xFF000000) >> (8 * 3);
    g = (hex & 0x00FF0000) >> (8 * 2);
    b = (hex & 0x0000FF00) >> (8 * 1);
    a = (hex & 0x000000FF) >> (8 * 0);
}

graphics::Color::Color(const sf::Color &color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

graphics::Color::Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) : r(r), g(g), b(b), a(a) {}

sf::Color graphics::Color::getSFColor() const {
    return {r, g, b, a};
}
