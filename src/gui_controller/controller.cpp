#include "controller.h"

#include "states/exit.h"
#include "states/game.h"
#include "states/main_menu.h"
#include "states/settings.h"

namespace gui {

Controller::Controller(graphics::Renderer &renderer, engine::Engine &engine) :
    m_renderer(renderer), m_engine(engine) {
    addState<Game>(GUIState::kGame);
    addState<MainMenu>(GUIState::kMainMenu);
    addState<Settings>(GUIState::kSettings);
    addState<Exit>(GUIState::kExit);
    changeState(GUIState::kMainMenu);
}

};   // namespace gui