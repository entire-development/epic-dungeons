#include "dungeon/makers/dungeon-maker.h"
#include "gui_controller/controller.h"
#include "keyboard/keyboard.h"
#include "renderer/graphics.h"
#include "static_data/game_config.h"
#include <SFML/Graphics.hpp>
#include <chrono>

int main() {
    graphics::Rectangle fps_rect = {0, 0, 100, 20, "#000000"};

    auto window = sf::RenderWindow {{cfg::WINDOW_WIDTH, cfg::WINDOW_HEIGHT},
                                    cfg::WINDOW_NAME,
                                    sf::Style::Titlebar | sf::Style::Close};
    window.setFramerateLimit(cfg::FRAMERATE);
    // window.setVerticalSyncEnabled(true);

    auto renderer = std::make_shared<graphics::Renderer>(window);
    auto engine = std::make_shared<engine::Engine>();

    dungeon::DungeonMaker dungeon_maker;
    dungeon_maker.setRandomSeed();
    dungeon_maker.build();
    engine->bindDungeon(dungeon_maker.getDungeon());

    gui::Controller controller;
    controller.bindEngine(engine);
    controller.bindRenderer(renderer);
    uint64_t last_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    int fps = 0;
    const int frames_to_average = 5;
    uint64_t accumulated_time = 0;
    int frames_counter = 0;

    while (window.isOpen()) {
        uint64_t current_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();
        uint64_t delta_time = current_time - last_time;
        frames_counter++;

        accumulated_time += delta_time;

        if (frames_counter == frames_to_average) {
            uint64_t average_time = accumulated_time / frames_to_average;
            
            if (average_time != 0) {
                fps = 1000 / average_time;
            } else {
                fps = 0;
            }
            frames_counter = 0;
            accumulated_time = 0;
        }

        last_time = current_time;

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
        if (cfg::FPS_COUNTER) {
            renderer->drawRec(fps_rect);
            renderer->draw(graphics::Text(std::to_string(fps), "arial", 20), 0, 0);
            renderer->display();
        }
    }
    return 0;
}
