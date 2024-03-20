#pragma once
#include "engine/item.h"
#include <memory>

namespace engine {
namespace items {

struct Longsword : public Weapon {
    Longsword() : Weapon() {
        id = "longsword";
        name = "Longsword";
        attackMod = 0;
        minDamage = 6;
        maxDamage = 12;
        criticalChanceMod = 3;
        speedMod = 1;
    }
};

}   // namespace items
}   // namespace engine
