#include "static-data/game-config.h"
#include "sfml-renderer.h"
#include "input/input.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace Renderer;

SFMLRenderer::SFMLRenderer() :
    IRenderer(),
    window(sf::RenderWindow{ { WINDOW_WIDTH, WINDOW_HEIGHT }, WINDOW_NAME })
{
    animation_timer = 0;
    window.setFramerateLimit(FRAMERATE);
}

void SFMLRenderer::updateState(uint64_t deltatime) {
    Input::InputController& controller = Input::InputController::getInstance();

    //bool temp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

    for (auto const& [control_type, sfml_value] : SFMLControls) {
        controller.setControl(control_type, sf::Keyboard::isKeyPressed(sfml_value));
    }

    animation_timer = animation_timer + deltatime;
    for (auto event = sf::Event{}; window.pollEvent(event);) {
        if (event.type == sf::Event::Closed) window.close();
    }
    window.clear();
}

void SFMLRenderer::drawCanvas() {
    window.display();
}

void SFMLRenderer::drawSprite(int x, int y, std::string sprite_id) {
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color(100, 250, 50));
    window.draw(shape);
}

void SFMLRenderer::drawText(int x, int y, std::string line) { }

void SFMLRenderer::drawRec(Rectangle rectangle) {
    sf::RectangleShape new_rectangle;
    new_rectangle.setSize(sf::Vector2f(rectangle.w, rectangle.h));
    new_rectangle.setFillColor(sf::Color::Cyan);
    new_rectangle.setOutlineColor(sf::Color::Cyan);
    new_rectangle.setOutlineThickness(5);
    new_rectangle.setPosition(rectangle.x, rectangle.y);
    window.draw(new_rectangle);
}
