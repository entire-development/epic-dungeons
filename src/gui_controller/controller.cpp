#include "controller.h"

#include "states/exit.h"
#include "states/game.h"
#include "states/main_menu.h"
#include "states/settings.h"
#include "states/dialogue_demo.h"

namespace gui {

Controller::Controller() : delta_time(0) {
    addState<Game>(GUIState::kGame);
    addState<MainMenu>(GUIState::kMainMenu);
    addState<Settings>(GUIState::kSettings);
    addState<Exit>(GUIState::kExit);
    addState<DialogueDemo>(GUIState::kDialogueDemo);
    changeState(GUIState::kDialogueDemo);
}

};   // namespace gui
