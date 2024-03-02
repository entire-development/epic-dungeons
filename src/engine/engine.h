#pragma once
#include "fsm/fsm.h"
#pragma "engine/states.h"

namespace engine {

enum class EngineState {
    kInCell,
    kRoomSelection,
    kDirectionChoice,
};

class Engine : public fsm::StateMachine<EngineState> {};
}   // namespace engine