#include "game_machine.h"
#include "states/main.h"
#include "states/room_selection.h"

namespace gui {
namespace game {
GameMachine::GameMachine() {
    addState<Main>(GUIGameState::kMain);
    addState<RoomSelection>(GUIGameState::kRoomSelection);
    changeState(GUIGameState::kMain);
}

}   // namespace game
}   // namespace gui