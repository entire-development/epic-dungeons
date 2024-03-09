#include "game_machine.h"
#include "states/empty.h"
#include "states/event.h"
#include "states/fight.h"
#include "states/main.h"
#include "states/post_event.h"
#include "states/room_selection.h"

namespace gui {
namespace game {
GameMachine::GameMachine() {
    addState<Main>(GUIGameState::kMain);
    addState<RoomSelection>(GUIGameState::kRoomSelection);
    addState<Fight>(GUIGameState::kFight);
    addState<Empty>(GUIGameState::kEmpty);
    addState<Event>(GUIGameState::kEvent);
    addState<PostEvent>(GUIGameState::kPostEvent);
    changeState(GUIGameState::kMain);
}

}   // namespace game
}   // namespace gui
