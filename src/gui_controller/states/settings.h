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

        static graphics::Sprite background = graphics::Sprite("background/main_menu/background.png").toSizeX(cfg::WINDOW_WIDTH);
        renderer->draw(background, 0, 0);

        int center = cfg::WINDOW_WIDTH * 14 / 36;

        // Current resolution
        renderer->draw(graphics::Text("Resolution: " + std::to_string(cfg::WINDOW_WIDTH) + "x" + std::to_string(cfg::WINDOW_HEIGHT), "story", 50),
                        center, 50);
        // Frame rate
        renderer->draw(graphics::Text("Frame rate: " + std::to_string(cfg::FRAMERATE), "story", 50), center, 100);
        // Controls
        renderer->draw(graphics::Text("Controls:", "story", 50), center, 200);
        renderer->draw(graphics::Text("Move down: " + keyboard::keyToString(cfg::CONTROLS_MOVE_DOWN), "story", 50), center, 250);
        renderer->draw(graphics::Text("Move left: " + keyboard::keyToString(cfg::CONTROLS_MOVE_LEFT), "story", 50), center, 300);
        renderer->draw(graphics::Text("Move right: " + keyboard::keyToString(cfg::CONTROLS_MOVE_RIGHT), "story", 50), center, 350);
        renderer->draw(graphics::Text("Action: " + keyboard::keyToString(cfg::CONTROLS_ACTION), "story", 50), center, 400);
        renderer->draw(graphics::Text("Close: " + keyboard::keyToString(cfg::CONTROLS_CLOSE), "story", 50), center, 450);
        renderer->draw(graphics::Text("Secondary: " + keyboard::keyToString(cfg::CONTROLS_SECONDARY), "story", 50), center, 500);

        // Back
        renderer->draw(graphics::Text("Press ESC to go back", "story", 50), center, 550);
        renderer->draw(graphics::Text("Press F to and on/off fps counter", "story", 50), center, 600);
        renderer->display();
    }

private:
    KeyboardManager k_manager;
};
}   // namespace gui
