#pragma once
#include "renderer/sfml_renderer/sfml_renderer.h"

namespace gui {

class View {
public:
    virtual void draw() = 0;

    virtual void bindRenderer(const renderer::SFMLRenderer &renderer) {
        m_renderer = const_cast<renderer::SFMLRenderer *>(&renderer);
    }

protected:
    renderer::SFMLRenderer *m_renderer;
};

}   // namespace gui
