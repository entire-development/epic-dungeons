#pragma once

#include "gui_controller/controller.h"
#include "static_data/game_config.h"

namespace gui {
class Game : public State {
public:
    uint64_t anim_time = 0;

    void enter(Controller *controller) {
        render(controller->m_renderer);
    }

    void update(Controller *controller) {
        render(controller->m_renderer);
        if (keyboard::isPressed(keyboard::KEY_ESCAPE)) {
            controller->changeState(GUIState::kMainMenu);
        }
    }

    void render(renderer::SFMLRenderer &renderer) {
        renderer.clear();
        renderer.drawText(400, 300, "This is game of imagination");

        // Animation
        anim_time += renderer.getDeltaTime();
        if (anim_time >= 1000) {
            anim_time -= 1000;
        }
        renderer.drawText(400, 400, "Animation frame: " + std::to_string(anim_time / 250));
        renderer.drawText(400, 430, "Loading" + std::string(anim_time / 250, '.'));

        // Back
        renderer.drawText(100, 500, "Press ESC to go back");
        renderer.display();
    }
};
}   // namespace gui