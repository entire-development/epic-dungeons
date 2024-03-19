#pragma once
#include "engine/item.h"
#include <memory>

namespace engine {
namespace items {

struct Glaive : public Weapon {
    id = "glaive";
    name = "Glaive";
    attackMod = 0;
    minDamage = 6;
    maxDamage = 12;
    criticalChanceMod = 5;
    speedMod = 4;
};

}   // namespace items
}   // namespace engine
