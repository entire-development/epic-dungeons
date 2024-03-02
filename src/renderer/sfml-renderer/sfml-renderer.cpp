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

Input::Key SFMLRenderer::handleSFMLKey(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Num1:        return Input::Key::KEY_1;
        case sf::Keyboard::Num2:        return Input::Key::KEY_2;
        case sf::Keyboard::Num3:        return Input::Key::KEY_3;
        case sf::Keyboard::Num4:        return Input::Key::KEY_4;
        case sf::Keyboard::Num5:        return Input::Key::KEY_5;
        case sf::Keyboard::Num6:        return Input::Key::KEY_6;
        case sf::Keyboard::Num7:        return Input::Key::KEY_7;
        case sf::Keyboard::Num8:        return Input::Key::KEY_8;
        case sf::Keyboard::Num9:        return Input::Key::KEY_9;
        case sf::Keyboard::Num0:        return Input::Key::KEY_0;
        case sf::Keyboard::A:           return Input::Key::KEY_A;
        case sf::Keyboard::B:           return Input::Key::KEY_B;
        case sf::Keyboard::C:           return Input::Key::KEY_C;
        case sf::Keyboard::D:           return Input::Key::KEY_D;
        case sf::Keyboard::E:           return Input::Key::KEY_E;
        case sf::Keyboard::F:           return Input::Key::KEY_F;
        case sf::Keyboard::G:           return Input::Key::KEY_G;
        case sf::Keyboard::H:           return Input::Key::KEY_H;
        case sf::Keyboard::I:           return Input::Key::KEY_I;
        case sf::Keyboard::J:           return Input::Key::KEY_J;
        case sf::Keyboard::K:           return Input::Key::KEY_K;
        case sf::Keyboard::L:           return Input::Key::KEY_L;
        case sf::Keyboard::M:           return Input::Key::KEY_M;
        case sf::Keyboard::N:           return Input::Key::KEY_N;
        case sf::Keyboard::O:           return Input::Key::KEY_O;
        case sf::Keyboard::P:           return Input::Key::KEY_P;
        case sf::Keyboard::Q:           return Input::Key::KEY_Q;
        case sf::Keyboard::R:           return Input::Key::KEY_R;
        case sf::Keyboard::S:           return Input::Key::KEY_S;
        case sf::Keyboard::T:           return Input::Key::KEY_T;
        case sf::Keyboard::U:           return Input::Key::KEY_U;
        case sf::Keyboard::V:           return Input::Key::KEY_V;
        case sf::Keyboard::W:           return Input::Key::KEY_W;
        case sf::Keyboard::X:           return Input::Key::KEY_X;
        case sf::Keyboard::Y:           return Input::Key::KEY_Y;
        case sf::Keyboard::Z:           return Input::Key::KEY_Z;
        case sf::Keyboard::Up:          return Input::Key::KEY_UP;
        case sf::Keyboard::Down:        return Input::Key::KEY_DOWN;
        case sf::Keyboard::Left:        return Input::Key::KEY_LEFT;
        case sf::Keyboard::Right:       return Input::Key::KEY_RIGHT;
        case sf::Keyboard::Space:       return Input::Key::KEY_SPACE;
        case sf::Keyboard::Return:      return Input::Key::KEY_ENTER;
        case sf::Keyboard::Escape:      return Input::Key::KEY_ESCAPE;
        case sf::Keyboard::BackSpace:   return Input::Key::KEY_BACKSPACE;
        case sf::Keyboard::Tab:         return Input::Key::KEY_TAB;
        case sf::Keyboard::LShift:      return Input::Key::KEY_SHIFT;
        case sf::Keyboard::LControl:    return Input::Key::KEY_CTRL;
        case sf::Keyboard::LAlt:        return Input::Key::KEY_ALT;
        case sf::Keyboard::LSystem:     return Input::Key::KEY_SUPER;
        default:                        return Input::Key::UNKNOWN;
    }
}

void SFMLRenderer::updateState(uint64_t deltatime) {
    Input::InputController& controller = Input::InputController::getInstance();

    animation_timer = animation_timer + deltatime;
    for (auto event = sf::Event{}; window.pollEvent(event);) {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::KeyPressed) {
            Input::Key key = handleSFMLKey(event.key.code);
            controller.setKeyState(key, true);
        }
        if (event.type == sf::Event::KeyReleased) {
            Input::Key key = handleSFMLKey(event.key.code);
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
    new_rectangle.setFillColor(sf::Color::Cyan);
    new_rectangle.setOutlineColor(sf::Color::Cyan);
    new_rectangle.setOutlineThickness(5);
    new_rectangle.setPosition(rectangle.x, rectangle.y);
    window.draw(new_rectangle);
}
