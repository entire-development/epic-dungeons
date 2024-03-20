#pragma once

#include "engine/item.h"

namespace engine {
namespace items {

struct AntiquarianArmor : public Armor {
    AntiquarianArmor() : Armor() {
    id = "antiquarian_armor";
    name = "Antiquarian Armor";
    defenseMod = 10;
    protectionMod = 0;
    speedMod = 0;
    }
};

}   // namespace items
}   // namespace engine
