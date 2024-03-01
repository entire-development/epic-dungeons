#include <game/game.h>
#include <iostream>
#include "renderer/renderer.h"

int main() {
    Game game;
    auto renderer = Renderer::SFMLRenderer();
        uint64_t deltatime_placeholder = 0;

        renderer.start();

        // game loop emulation
        while (renderer.isActive()) {
            renderer.update(deltatime_placeholder);
        }

    return 0;
}