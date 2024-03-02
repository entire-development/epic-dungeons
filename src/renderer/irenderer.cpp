#include <iostream>
#include "irenderer.h"

using namespace Renderer;

IRenderer::IRenderer() :
    animation_timer(0),
    active(false) {}


void IRenderer::start() {
    active = true;
}

void IRenderer::finish() {
    active = false;
}

bool IRenderer::isActive() {
    return active;
}
