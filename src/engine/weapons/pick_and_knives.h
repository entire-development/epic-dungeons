#pragma once
#include "engine/item.h"
#include <memory>

namespace engine {
namespace items {

struct PickAndKnives : public Weapon {
    PickAndKnives() : Weapon() {
    id = "pick_and_knives";
    name = "Pick and Knives";
    attackMod = 0;
    minDamage = 4;
    maxDamage = 8;
    criticalChanceMod = 6;
    speedMod = 8;
    }
};

}   // namespace items
}   // namespace engine
