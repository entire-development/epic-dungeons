#pragma once

#include "engine/item.h"

namespace engine {
namespace items {

struct BountyHunterArmor : public Armor {
    BountyHunterArmor() : Armor(){
    id = "bounty_hunter_armor";
    name = "Bounty Hunter Armor";
    defenseMod = 5;
    protectionMod = 0;
    speedMod = 0;
    }
};

}   // namespace items
}   // namespace engine
