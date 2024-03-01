#include "view/renderer/sfml-renderer/sfml-renderer.h"
#include "game-config.h"
#include <iostream>

SFMLRenderer::SFMLRenderer() :
    IRenderer(),
    window(sf::RenderWindow{ { WINDOW_WIDTH, WINDOW_HEIGHT }, WINDOW_NAME })
{
    animation_timer = 0;
    window.setFramerateLimit(FRAMERATE);
}

KeyboardEvent SFMLRenderer::update(uint64_t deltatime) {
    KeyboardEvent event_keycode = {0, 0};
    animation_timer = animation_timer + deltatime;
    for (auto event = sf::Event{}; window.pollEvent(event);) {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::KeyPressed) event_keycode.type = 1;
        if (event.type == sf::Event::KeyReleased) event_keycode.type = 2;

        event_keycode.code = event.key.code;
    }
    prev_keyboard_event = event_keycode;

    window.clear();
    window.display();

    return event_keycode;
}

int SFMLRenderer::draw_sprite(int x, int y, std::string sprite_id) {
    return 0;
}

int SFMLRenderer::draw_text(int x, int y, std::string line) {
    return 0;
}

int SFMLRenderer::draw_rec(int x, int y, int w, int h, std::string color, std::string stroke_color, int stroke_weight) {
    return 0;
}
