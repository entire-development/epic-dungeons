#include "view/renderer/irenderer/irenderer.h"
#include <iostream>

IRenderer::IRenderer()  : animation_timer(0), active(false), prev_keyboard_event({0, 0}) {}

KeyboardEvent IRenderer::get_prev_keyboard_event() {
    return prev_keyboard_event;
}

void IRenderer::start() {
    active = true;
}

void IRenderer::close() {
    active = false;
}

bool IRenderer::is_active() {
    return active;
}
