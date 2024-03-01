/*
 *  created by QUASARITY 27.02.2024. Temp file!!! May be deleted later.
 */
#include "view/renderer/sfml-renderer/sfml-renderer.h"

int main() {
    SFMLRenderer renderer = SFMLRenderer();
    uint64_t deltatime_placeholder = 0;

    renderer.start();

    // game loop emulation
    while (renderer.isActive()) {
        renderer.update(deltatime_placeholder);
    }
}
