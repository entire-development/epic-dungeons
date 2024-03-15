#pragma once

#include "engine/item.h"

namespace engine {
namespace items {

struct HighwaymanArmor : public Armor {
    const std::string name = "Highwayman Armor";
    const int32_t defenseMod = 5;
    const int32_t protectionMod = 5;
    const int32_t speedMod = 5;
};

}   // namespace items
}   // namespace engine