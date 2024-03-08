#include "graphics.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <sstream>

namespace graphics {

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
    new_rectangle.setFillColor(rectangle.color.toSF());
    new_rectangle.setOutlineColor(rectangle.stroke_color.toSF());
    new_rectangle.setOutlineThickness(rectangle.stroke);
    new_rectangle.setPosition(rectangle.x, rectangle.y);
    window.draw(new_rectangle);
}

void Renderer::draw(const Text &text, int x, int y) {
    sf::Text set_text = text.toSF();
    set_text.setPosition(x, y);
    window.draw(set_text);
}

void Renderer::draw(const Sprite &sprite, int x, int y) {
    sf::Sprite set_sprite = sprite.toSF();
    set_sprite.setPosition(x, y);
    window.draw(set_sprite);
}

}   // namespace graphics
