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
            if (inputController.isMoveTop()) {
                renderer.drawRec(Renderer::Rectangle{90, 20, 50, 50, 0x00ffff00, 0, 0x00000000});
            }

            if (inputController.isMoveLeft()) {
                renderer.drawRec(Renderer::Rectangle{20, 90, 50, 50, 0x00ffff00, 0, 0x00000000});
            }

            if (inputController.isMoveDown()) {
                renderer.drawRec(Renderer::Rectangle{90, 90, 50, 50, 0x00ffff00, 0, 0x00000000});
            }

            if (inputController.isMoveRight()) {
                renderer.drawRec(Renderer::Rectangle{160, 90, 50, 50, 0x00ffff00, 0, 0x00000000});
            }

            if (inputController.isAction()) {
                renderer.drawRec(Renderer::Rectangle{20, 200, 50, 50, 0x00ffff00, 0, 0x00000000});
            }

            if (inputController.isClose()) {
                renderer.drawRec(Renderer::Rectangle{90, 200, 50, 50, 0x00ffff00, 0, 0x00000000});
            }

            if (inputController.isSecondary()) {
                renderer.drawRec(Renderer::Rectangle{160, 200, 50, 50, 0x00ffff00, 0, 0x00000000});
            }

            renderer.drawCanvas();
        }

    return 0;
}