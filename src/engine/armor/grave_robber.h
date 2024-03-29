#pragma once

#include "engine/item.h"

namespace engine {
namespace items {

struct GraveRobberArmor : public Armor {
    GraveRobberArmor() : Armor() {
        id = "grave_robber_armor";
        name = "Grave Robber Armor";
        defenseMod = 10;
        protectionMod = 0;
        speedMod = 0;
    }
};

}   // namespace items
}   // namespace engine
