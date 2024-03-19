#pragma once
#include <memory>

namespace engine {
namespace entities {}   // namespace entities

namespace items {
struct Weapon {
    std::string id;
    std::string name;
    int32_t attackMod = 0;
    int32_t minDamage = 0;
    int32_t maxDamage = 0;
    int32_t criticalChanceMod = 0;
    int32_t speedMod = 0;
};

struct Armor {
    std::string id;
    std::string name;
    int32_t defenseMod = 0;
    int32_t protectionMod = 0;
    int32_t speedMod = 0;
};

}   // namespace items
}   // namespace engine
