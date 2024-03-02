#include "static_data/game_config.h"
#include "sfml_renderer.h"
#include "keyboard/keyboard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace Renderer;

SFMLRenderer::SFMLRenderer() :
    IRenderer(),
    window(sf::RenderWindow{ { WINDOW_WIDTH, WINDOW_HEIGHT }, WINDOW_NAME })
{
    animation_timer = 0;
    window.setFramerateLimit(FRAMERATE);
}

Keyboard::Key SFMLRenderer::handleSFMLKey(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Num1:        return Keyboard::Key::KEY_1;
        case sf::Keyboard::Num2:        return Keyboard::Key::KEY_2;
        case sf::Keyboard::Num3:        return Keyboard::Key::KEY_3;
        case sf::Keyboard::Num4:        return Keyboard::Key::KEY_4;
        case sf::Keyboard::Num5:        return Keyboard::Key::KEY_5;
        case sf::Keyboard::Num6:        return Keyboard::Key::KEY_6;
        case sf::Keyboard::Num7:        return Keyboard::Key::KEY_7;
        case sf::Keyboard::Num8:        return Keyboard::Key::KEY_8;
        case sf::Keyboard::Num9:        return Keyboard::Key::KEY_9;
        case sf::Keyboard::Num0:        return Keyboard::Key::KEY_0;
        case sf::Keyboard::A:           return Keyboard::Key::KEY_A;
        case sf::Keyboard::B:           return Keyboard::Key::KEY_B;
        case sf::Keyboard::C:           return Keyboard::Key::KEY_C;
        case sf::Keyboard::D:           return Keyboard::Key::KEY_D;
        case sf::Keyboard::E:           return Keyboard::Key::KEY_E;
        case sf::Keyboard::F:           return Keyboard::Key::KEY_F;
        case sf::Keyboard::G:           return Keyboard::Key::KEY_G;
        case sf::Keyboard::H:           return Keyboard::Key::KEY_H;
        case sf::Keyboard::I:           return Keyboard::Key::KEY_I;
        case sf::Keyboard::J:           return Keyboard::Key::KEY_J;
        case sf::Keyboard::K:           return Keyboard::Key::KEY_K;
        case sf::Keyboard::L:           return Keyboard::Key::KEY_L;
        case sf::Keyboard::M:           return Keyboard::Key::KEY_M;
        case sf::Keyboard::N:           return Keyboard::Key::KEY_N;
        case sf::Keyboard::O:           return Keyboard::Key::KEY_O;
        case sf::Keyboard::P:           return Keyboard::Key::KEY_P;
        case sf::Keyboard::Q:           return Keyboard::Key::KEY_Q;
        case sf::Keyboard::R:           return Keyboard::Key::KEY_R;
        case sf::Keyboard::S:           return Keyboard::Key::KEY_S;
        case sf::Keyboard::T:           return Keyboard::Key::KEY_T;
        case sf::Keyboard::U:           return Keyboard::Key::KEY_U;
        case sf::Keyboard::V:           return Keyboard::Key::KEY_V;
        case sf::Keyboard::W:           return Keyboard::Key::KEY_W;
        case sf::Keyboard::X:           return Keyboard::Key::KEY_X;
        case sf::Keyboard::Y:           return Keyboard::Key::KEY_Y;
        case sf::Keyboard::Z:           return Keyboard::Key::KEY_Z;
        case sf::Keyboard::Up:          return Keyboard::Key::KEY_UP;
        case sf::Keyboard::Down:        return Keyboard::Key::KEY_DOWN;
        case sf::Keyboard::Left:        return Keyboard::Key::KEY_LEFT;
        case sf::Keyboard::Right:       return Keyboard::Key::KEY_RIGHT;
        case sf::Keyboard::Space:       return Keyboard::Key::KEY_SPACE;
        case sf::Keyboard::Return:      return Keyboard::Key::KEY_ENTER;
        case sf::Keyboard::Escape:      return Keyboard::Key::KEY_ESCAPE;
        case sf::Keyboard::BackSpace:   return Keyboard::Key::KEY_BACKSPACE;
        case sf::Keyboard::Tab:         return Keyboard::Key::KEY_TAB;
        case sf::Keyboard::LShift:      return Keyboard::Key::KEY_SHIFT;
        case sf::Keyboard::LControl:    return Keyboard::Key::KEY_CTRL;
        case sf::Keyboard::LAlt:        return Keyboard::Key::KEY_ALT;
        case sf::Keyboard::LSystem:     return Keyboard::Key::KEY_SUPER;
        default:                        return Keyboard::Key::UNKNOWN;
    }
}

void SFMLRenderer::updateState(uint64_t deltatime) {
    Keyboard::KeyboardController& controller = Keyboard::KeyboardController::getInstance();

    animation_timer = animation_timer + deltatime;
    for (auto event = sf::Event{}; window.pollEvent(event);) {
        if (event.type == sf::Event::Closed) finish();

        if (event.type == sf::Event::KeyPressed) {
            Keyboard::Key key = handleSFMLKey(event.key.code);
            controller.setKeyState(key, true);
        }
        if (event.type == sf::Event::KeyReleased) {
            Keyboard::Key key = handleSFMLKey(event.key.code);
            controller.setKeyState(key, false);
        }
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
    new_rectangle.setFillColor(rectangle.color.getSFColor());
    new_rectangle.setOutlineColor(rectangle.stroke_color.getSFColor());
    new_rectangle.setOutlineThickness(5);
    new_rectangle.setPosition(rectangle.x, rectangle.y);
    window.draw(new_rectangle);
}

Color::Color(sf::Color color) : sfcolor(color) {}

Color::Color(std::string hex_str) {
    if (hex_str[0] != '#') {
        sfcolor = sf::Color(0x00000000);
        return;
    }
    if (hex_str.length() < 7 || hex_str.length() > 9) {
        sfcolor = sf::Color(0x00000000);
        return;
    }
    uint32_t hex;
    std::stringstream ss;
    ss << std::hex << (hex_str.substr(1, hex_str.length() - 1) + "ff");
    ss >> hex;
    sfcolor = sf::Color(hex);
}

Color::Color(uint32_t hex) : sfcolor(sf::Color(hex)) {}

std::string Color::toHexString() const {
    std::stringstream ss;
    ss << std::hex << "#" << +sfcolor.r << +sfcolor.g << +sfcolor.b;
    std::string result( ss.str() );
    return result;
}

inline sf::Color Color::getSFColor() const {
    return sfcolor;
}