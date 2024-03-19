#pragma once
#include "engine/item.h"
#include <memory>

namespace engine {
namespace items {

struct AbandonedAxe : public Weapon {
    id = "abandoned_axe";
    name = "Abandoned Axe";
    attackMod = 0;
    minDamage = 5;
    maxDamage = 10;
    criticalChanceMod = 4;
    speedMod = 5;
};

}   // namespace items
}   // namespace engine
