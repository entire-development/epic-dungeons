#include "game_machine.h"
#include "states/cell_movement.h"
#include "states/empty.h"
#include "states/event.h"
#include "states/fight.h"
#include "states/main.h"
#include "states/move_transition.h"
#include "states/post_event.h"

namespace gui {
namespace game {
GameMachine::GameMachine() {
    addState<Main>(GUIGameState::kMain);
    addState<CellMovement>(GUIGameState::kCellMovement);
    addState<MoveTransition>(GUIGameState::kMoveTransition);
    addState<Fight>(GUIGameState::kFight);
    addState<Empty>(GUIGameState::kEmpty);
    addState<Event>(GUIGameState::kEvent);
    addState<PostEvent>(GUIGameState::kPostEvent);
    //changeState(GUIGameState::kMain);
}

}   // namespace game
}   // namespace gui
