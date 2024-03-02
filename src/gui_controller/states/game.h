#pragma once

#include "gui_controller/controller.h"
#include "static_data/game_config.h"

namespace gui {
class Game : public State {
public:
    void enter(Controller *controller) {
        render(controller->m_renderer);
    }

    void update(Controller *controller) {
        if (keyboard::isPressed(keyboard::KEY_ESCAPE)) {
            controller->changeState(GUIState::kMainMenu);
        }
    }

    void render(renderer::SFMLRenderer &renderer) {
        renderer.clear();
        renderer.drawText(400, 300, "This is game of imagination");

        // Back
        renderer.drawText(100, 500, "Press ESC to go back");
        renderer.display();
    }
};
}   // namespace gui