#pragma once

#include "engine/item.h"

namespace engine {
namespace items {

struct ArbalestArmor : public Armor {
    ArbalestArmor : Armor() {
    id = "arbalest_armor";
    name = "Arbalest Armor";
    defenseMod = 0;
    protectionMod = 0;
    speedMod = 0;
    }
};

}   // namespace items
}   // namespace engine
