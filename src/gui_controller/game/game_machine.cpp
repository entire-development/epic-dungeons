#include "game_machine.h"
#include "states/main.h"

namespace gui {
namespace game {
GameMachine::GameMachine() {
    addState<Main>(GUIGameState::kMain);
    changeState(GUIGameState::kMain);
}

}   // namespace game
}   // namespace gui