#include "graphics.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <SFML/Graphics.hpp>
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

// TODO: refactor
//Color::Color(const sf::Color &color) : sfcolor(color) {}
//
//Color::Color(const std::string &hex_str) {
//    if (hex_str[0] != '#') {
//        sfcolor = sf::Color(0x00000000);
//        return;
//    }
//    if (hex_str.length() < 7 || hex_str.length() > 9) {
//        sfcolor = sf::Color(0x00000000);
//        return;
//    }
//    uint32_t hex;
//    std::stringstream ss;
//    ss << std::hex << (hex_str.substr(1, hex_str.length() - 1) + "ff");
//    ss >> hex;
//    sfcolor = sf::Color(hex);
//}
//
//Color::Color(const uint32_t &hex) : sfcolor(sf::Color(hex)) {}
//
//const std::string Color::toHexString() const {
//    std::stringstream ss;
//    ss << std::hex << "#" << +sfcolor.r << +sfcolor.g << +sfcolor.b;
//    std::string result(ss.str());
//    return result;
//}
//
//inline const sf::Color Color::getSFColor() const {
//    return sfcolor;
//}
