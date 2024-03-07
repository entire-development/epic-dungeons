#include "controller.h"

#include "states/exit.h"
#include "states/game.h"
#include "states/main_menu.h"
#include "states/settings.h"

namespace gui {

Controller::Controller() : delta_time(0) {
    addState<Game>(GUIState::kGame);
    addState<MainMenu>(GUIState::kMainMenu);
    addState<Settings>(GUIState::kSettings);
    addState<Exit>(GUIState::kExit);
    changeState(GUIState::kMainMenu);
}

};   // namespace gui