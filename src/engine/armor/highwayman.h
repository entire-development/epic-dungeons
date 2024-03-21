#pragma once

#include "engine/item.h"

namespace engine {
namespace items {

struct HighwaymanArmor : public Armor {
    HighwaymanArmor() : Armor() {
        id = "highwayman_armor";
        name = "Highwayman Armor";
        defenseMod = 5;
        protectionMod = 5;
        speedMod = 0;
    }
};

}   // namespace items
}   // namespace engine
