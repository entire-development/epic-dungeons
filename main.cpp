#include "keyboard/keyboard.h"
#include "renderer/sfml_renderer/sfml_renderer.h"
#include "static_data/game_config.h"
#include <SFML/Graphics.hpp>

int main() {
    auto window = sf::RenderWindow {{cfg::WINDOW_WIDTH, cfg::WINDOW_HEIGHT}, cfg::WINDOW_NAME};
    window.setFramerateLimit(cfg::FRAMERATE);

    auto renderer = renderer::SFMLRenderer(window);

    while (window.isOpen()) {
        renderer.updateState(1);

        for (auto event = sf::Event {}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                keyboard::setKeyState(event.key.code, true);
            }
            if (event.type == sf::Event::KeyReleased) {
                keyboard::setKeyState(event.key.code, false);
            }
        }

        if (keyboard::isPressed(cfg::CONTROLS_MOVE_UP)) {
            renderer.drawRec({100, 100, 100, 100, sf::Color::Red});
        }
        if (keyboard::isPressed(cfg::CONTROLS_MOVE_DOWN)) {
            renderer.drawRec({200, 200, 100, 100, sf::Color::Green});
        }
        if (keyboard::isPressed(cfg::CONTROLS_MOVE_LEFT)) {
            renderer.drawRec({300, 300, 100, 100, sf::Color::Blue});
        }
        if (keyboard::isPressed(cfg::CONTROLS_MOVE_RIGHT)) {
            renderer.drawRec({400, 400, 100, 100, sf::Color::Yellow});
        }

        renderer.drawCanvas();
    }

    return 0;
}
