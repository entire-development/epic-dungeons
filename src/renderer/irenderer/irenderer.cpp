#include <iostream>
#include "irenderer.h"
#include "input/input.h"

using namespace Renderer;

IRenderer::IRenderer() :
    animation_timer(0),
    active(false),
    prev_keyboard_event({0, 0}) {}

Input::KeyboardEvent IRenderer::getPrevKeyboardEvent() {
    return prev_keyboard_event;
}

void IRenderer::start() {
    active = true;
}

void IRenderer::close() {
    active = false;
}

bool IRenderer::isActive() {
    return active;
}