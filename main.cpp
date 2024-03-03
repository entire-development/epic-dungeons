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
    uint64_t last_time = 0;
    while (window.isOpen()) {
        uint64_t current_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();
        uint64_t delta_time = current_time - last_time;
        last_time = current_time;

        renderer.updateState(delta_time);
        controller.setDeltaTime(delta_time);

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
