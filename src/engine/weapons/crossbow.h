#pragma once
#include "engine/item.h"
#include <memory>

namespace engine {
namespace items {

struct Crossbow : public Weapon {
    Crossbow() : Weapon() {
    id = "crossbow";
    name = "Crossbow";
    attackMod = 0;
    minDamage = 4;
    maxDamage = 8;
    criticalChanceMod = 6;
    speedMod = 3;
    }
};

}   // namespace items
}   // namespace engine
