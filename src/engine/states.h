#pragma once

#include "fsm/fsm.h"
#pragma "fsm/states.h"

namespace engine {
class Engine;

enum class EngineState {
    kInCell,
    kRoomSelection,
    kDirectionChoice,
};

}   // namespace engine