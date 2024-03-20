#pragma once

#include "engine/item.h"

namespace engine {
namespace items {

struct HellionArmor : public Armor {
    HellionArmor() : Armor() {
    id = "hellion_armor";
    name = "Hellion Armor";
    defenseMod = 10;
    protectionMod = 0;
    speedMod = 0;
    }
};

}   // namespace items
}   // namespace engine
