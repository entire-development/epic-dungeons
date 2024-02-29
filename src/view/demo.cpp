/*
 *  created by QUASARITY 27.02.2024. Temp file!!! May be deleted later.
 */
#include "view/renderer/sfml-renderer/sfml-renderer.h"

int main() {
    // init
    SFMLRenderer renderer = SFMLRenderer();
    uint64_t deltatime_placeholder = 0;

    // game loop emulation
    while (renderer.is_active()) {
        renderer.update(deltatime_placeholder);
    }
}
