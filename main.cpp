#include <game/game.h>
#include <iostream>
#include "renderer/sfml_renderer/sfml_renderer.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <SFML/Graphics.hpp>

Keyboard::Key handleSFMLKey(sf::Keyboard::Key key) {
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

int main() {
    Game game;

    auto window = sf::RenderWindow{ { WINDOW_WIDTH, WINDOW_HEIGHT }, WINDOW_NAME };
    window.setFramerateLimit(FRAMERATE);

    auto renderer = Renderer::SFMLRenderer(window);
    uint64_t deltatime_placeholder = 0;

    renderer.start();

    Keyboard::KeyboardController& inputController = Keyboard::KeyboardController::getInstance();

    Renderer::Color primary_color = Renderer::Color("#6666ff");

    // game loop emulation
    while (renderer.isActive()) {

        // events
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                Keyboard::Key key = handleSFMLKey(event.key.code);
                inputController.setKeyState(key, true);
            }
            if (event.type == sf::Event::KeyReleased) {
                Keyboard::Key key = handleSFMLKey(event.key.code);
                inputController.setKeyState(key, false);
            }
        }

        // drawing
        renderer.updateState(deltatime_placeholder);

        // an example of input-conditioned shape rendering
        if (inputController.isPressed(CONTROLS_MOVE_UP)) {
            renderer.drawRec(Renderer::Rectangle{90, 20, 50, 50, primary_color, 0, primary_color});
        }

        if (inputController.isPressed(CONTROLS_MOVE_DOWN)) {
            renderer.drawRec(Renderer::Rectangle{90, 90, 50, 50, primary_color, 0, primary_color});
        }

        renderer.drawCanvas();
    }

    return 0;
}
