#pragma once

#include "engine/item.h"

namespace engine {
namespace items {

struct AbominationArmor : public Armor {
    AbominationArmor() : Armor() {
        id = "abomination_armor";
        name = "Abomination Armor";
        defenseMod = 7;
        protectionMod = 0;
        speedMod = 0;
    }
};

}   // namespace items
}   // namespace engine
