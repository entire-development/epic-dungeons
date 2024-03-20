#pragma once

#include "gui_controller/controller.h"
#include "static_data/game_config.h"
#include "gui_controller/keyboard_manager/keyboard_manager.h"

namespace gui {
class Settings : public State {
public:
    void enter(Controller *controller) {
        render(controller->m_renderer.get());
        k_manager.reset();
    }

    void update(Controller *controller) {
        k_manager.update();
        if (k_manager.isClicked(keyboard::KEY_F)) {
            cfg::FPS_COUNTER ^= true;
        }

        if (keyboard::isPressed(keyboard::KEY_ESCAPE)) {
            controller->changeState(GUIState::kMainMenu);
        }
    }

    void render(graphics::Renderer *renderer) {
        renderer->clear();
        renderer->drawText(100, 100, "Settings");

        // Current resolution
        renderer->drawText(
            100, 150, "Resolution: " + std::to_string(cfg::WINDOW_WIDTH) + "x" + std::to_string(cfg::WINDOW_HEIGHT));
        // Frame rate
        renderer->drawText(100, 200, "Frame rate: " + std::to_string(cfg::FRAMERATE));
        // Controls
        renderer->drawText(100, 250, "Controls:");
        renderer->drawText(100, 280, "Move up: " + keyboard::keyToString(cfg::CONTROLS_MOVE_UP));
        renderer->drawText(100, 310, "Move down: " + keyboard::keyToString(cfg::CONTROLS_MOVE_DOWN));
        renderer->drawText(100, 340, "Move left: " + keyboard::keyToString(cfg::CONTROLS_MOVE_LEFT));
        renderer->drawText(100, 370, "Move right: " + keyboard::keyToString(cfg::CONTROLS_MOVE_RIGHT));
        renderer->drawText(100, 400, "Action: " + keyboard::keyToString(cfg::CONTROLS_ACTION));
        renderer->drawText(100, 430, "Close: " + keyboard::keyToString(cfg::CONTROLS_CLOSE));
        renderer->drawText(100, 460, "Secondary: " + keyboard::keyToString(cfg::CONTROLS_SECONDARY));
        renderer->drawText(100, 490, std::string("FPS Counter: ") + (cfg::FPS_COUNTER ? "ON" : "OFF"));

        // Back
        renderer->drawText(100, 530, "Press ESC to go back");
        renderer->drawText(100, 560, "Press F to pay respects and on/off fps counter");

        renderer->display();
    }

private:
    KeyboardManager k_manager;
};
}   // namespace gui
