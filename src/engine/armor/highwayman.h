#pragma once

#include "engine/weapon.h"

namespace engine {
namespace items {

struct HighwaymanArmor : public Armor {
    const std::string name = "highwayman_armor";
    const int32_t defenseMod = 10;
    const int32_t protectionMod = 0;
    const int32_t speedMod = 0;
};

}   // namespace items
}   // namespace engine