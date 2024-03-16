#pragma once
#include "engine/item.h"
#include <memory>

namespace engine {
namespace items {

struct Pistol : public Weapon {
    const std::string id = "pistol";
    const std::string name = "Pistol";
    const int32_t attackMod = 0;
    const int32_t minDamage = 5;
    const int32_t maxDamage = 10;
    const int32_t criticalChanceMod = 5;
    const int32_t speedMod = 5;
};

}   // namespace items
}   // namespace engine
