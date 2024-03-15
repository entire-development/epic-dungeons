#include "dungeon/makers/dungeon-maker.h"
#include "gui_controller/controller.h"
#include "keyboard/keyboard.h"
#include "renderer/graphics.h"
#include "static_data/game_config.h"
#include <SFML/Graphics.hpp>
#include <chrono>

int main() {
    graphics::Rectangle fps_rect;
    fps_rect.x = 0;
    fps_rect.y = 0;
    fps_rect.w = 100;
    fps_rect.h = 30;
    fps_rect.color = graphics::Color("#000000");
    bool fps_enabled = false;

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
    while (window.isOpen()) {
        uint64_t current_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();
        uint64_t delta_time = current_time - last_time;
        float fps = 1000.0f/delta_time;
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
        if (fps_enabled) {
            renderer->drawRec(fps_rect);
            renderer->draw(graphics::Text(std::to_string(fps), "arial", 20), 0, 0);
            renderer->display();
        }
    }
    return 0;
}
