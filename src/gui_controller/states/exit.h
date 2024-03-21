#pragma once
#include "gui_controller/controller.h"

namespace gui {
class Exit : public State {
public:
    void enter(Controller *controller) {
        controller->m_renderer->close();
    }
};
}   // namespace gui
