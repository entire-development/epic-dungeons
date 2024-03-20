#pragma once

#include "gui_controller/controller.h"
#include "static_data/game_config.h"

namespace gui {
class Settings : public State {
public:
    void enter(Controller *controller) {
        render(controller->m_renderer.get());
    }

    void update(Controller *controller) {
        bool pressed_f = keyboard::isPressed(keyboard::KEY_F);
        if (pressed_f != is_key_pressed) {
            is_key_pressed = pressed_f;
            render(controller->m_renderer.get());
        }

        if (keyboard::isPressed(keyboard::KEY_ESCAPE)) {
            controller->changeState(GUIState::kMainMenu);
        }
    }

    void render(graphics::Renderer *renderer) {
        renderer->clear();
        renderer->drawText(100, 100, "Settings");

        renderer->draw(graphics::Sprite("background/main_menu/background.png").toSizeX(cfg::WINDOW_WIDTH), 0, 0);

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

        // Back
        renderer->drawText(100, 500, "Press ESC to go back");
        renderer->drawText(100, 530, "Press F to pay respects");
        if (keyboard::isPressed(keyboard::KEY_F)) {
            renderer->drawText(80, 530, "F");
        }
        renderer->display();
    }

private:
    bool is_key_pressed = false;
};
}   // namespace gui
