#pragma once

#include "engine/item.h"

namespace engine {
namespace items {

struct CrusaderArmor : public Armor {
    id = "crusader_armor";
    name = "Crusader Armor";
    defenseMod = 10;
    protectionMod = 0;
    speedMod = 0;
};

}   // namespace items
}   // namespace engine
