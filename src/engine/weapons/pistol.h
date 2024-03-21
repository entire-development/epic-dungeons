#pragma once
#include "engine/item.h"
#include <memory>

namespace engine {
namespace items {

struct Pistol : public Weapon {
    Pistol() : Weapon() {
        id = "pistol";
        name = "Pistol";
        attackMod = 0;
        minDamage = 5;
        maxDamage = 10;
        criticalChanceMod = 5;
        speedMod = 5;
    }
};

}   // namespace items
}   // namespace engine
