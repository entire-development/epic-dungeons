#include <game/game.h>
#include <iostream>
#include "renderer/sfml_renderer/sfml_renderer.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"

int main() {
    Game game;

    auto renderer = Renderer::SFMLRenderer();
    uint64_t deltatime_placeholder = 0;

    renderer.start();

    Keyboard::KeyboardController& inputController = Keyboard::KeyboardController::getInstance();

    Renderer::Color primary_color = Renderer::Color("#6666ff");

    // game loop emulation
    while (renderer.isActive()) {
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
