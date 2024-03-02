#include "gui_controller/controller.h"
#include "keyboard/keyboard.h"
#include "renderer/sfml_renderer/sfml_renderer.h"
#include "static_data/game_config.h"
#include <SFML/Graphics.hpp>

int main() {
    auto window = sf::RenderWindow {{cfg::WINDOW_WIDTH, cfg::WINDOW_HEIGHT},
                                    cfg::WINDOW_NAME,
                                    sf::Style::Titlebar | sf::Style::Close};
    window.setFramerateLimit(cfg::FRAMERATE);
    window.setVerticalSyncEnabled(true);

    auto renderer = renderer::SFMLRenderer(window);
    engine::Engine engine;

    gui::Controller controller(renderer, engine);

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

        controller.update();
    }

    return 0;
}
