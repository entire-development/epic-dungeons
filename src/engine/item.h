#pragma once
#include <memory>

namespace engine {
namespace entities {}   // namespace entities

namespace items {
struct Weapon {
    const std::string id;
    const std::string name;
    const int32_t attackMod = 0;
    const int32_t minDamage = 0;
    const int32_t maxDamage = 0;
    const int32_t criticalChanceMod = 0;
    const int32_t speedMod = 0;
};

struct Armor {
    const std::string id;
    const std::string name;
    const int32_t defenseMod = 0;
    const int32_t protectionMod = 0;
    const int32_t speedMod = 0;
};

}   // namespace items
}   // namespace engine