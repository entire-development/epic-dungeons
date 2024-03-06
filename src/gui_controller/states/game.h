#pragma once

#include "gui_controller/controller.h"
#include "gui_controller/game/game_machine.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"

namespace gui {
class Game : public State {
public:
    Game() : State(), game_machine() {}

    game::GameMachine game_machine;

    void onEngineBind(std::weak_ptr<engine::Engine> engine) override {
        game_machine.bindEngine(engine);
    }

    void onRendererBind(std::weak_ptr<renderer::SFMLRenderer> renderer) override {
        game_machine.bindRenderer(renderer);
    }

    void enter(Controller *controller) override {
        game_machine.enter(controller);
    }

    void update(Controller *controller) override {
        if (keyboard::isPressed(keyboard::KEY_ESCAPE)) {
            controller->changeState(GUIState::kMainMenu);
            return;
        }
        game_machine.update(controller);
    }

    void exit(Controller *controller) override {
        game_machine.exit(controller);
    }
};

}   // namespace gui