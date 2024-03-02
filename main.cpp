#include <game/game.h>
#include <iostream>
#include "renderer/renderer.h"
#include "input/input.h"

int main() {
    Game game;
    auto renderer = Renderer::SFMLRenderer();
        uint64_t deltatime_placeholder = 0;

        renderer.start();

        Input::InputController& inputController = Input::InputController::getInstance();

        // game loop emulation
        while (renderer.isActive()) {
            renderer.updateState(deltatime_placeholder);
            if (inputController.isPressed(Input::Key::KEY_UP)) {
                renderer.drawRec(Renderer::Rectangle{90, 20, 50, 50, 0x00ffff00, 0, 0x00000000});
            }

            if (inputController.isPressed(Input::Key::KEY_DOWN)) {
                renderer.drawRec(Renderer::Rectangle{90, 90, 50, 50, 0x00ffff00, 0, 0x00000000});
            }

            renderer.drawCanvas();
        }

    return 0;
}