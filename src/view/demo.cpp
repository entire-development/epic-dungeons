/*
 * created by QUASARITY 27.02.2024. Temp file!!! May be deleted later.
 */
#include <SFML/Graphics.hpp>

int main() {
    auto window = sf::RenderWindow{ { 920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
