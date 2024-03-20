#pragma once
#include "engine/item.h"
#include <memory>

namespace engine {
namespace items {

struct IncubatingMutation : public Weapon {
    IncubatingMutation() : Weapon() {
    id = "incubating_mutation";
    name = "Incubating Mutation";
    attackMod = 0;
    minDamage = 6;
    maxDamage = 11;
    criticalChanceMod = 2;
    speedMod = 7;
    }
};

}   // namespace items
}   // namespace engine
