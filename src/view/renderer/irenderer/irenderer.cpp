#include "view/renderer/irenderer/irenderer.h"
#include <iostream>

KeyboardEvent IRenderer::get_prev_keyboard_event() {
    return prev_keyboard_event;
}

void IRenderer::start() {
    active = true;
}

void IRenderer::close() {
    active = false;
}
