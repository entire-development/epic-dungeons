#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct WickedSlice : public CombatSkill {
    const std::string id = "wicked_slice";
    const uint8_t level = 0;
    const Type type = Type::kMelee;
    const TargetType targetType = TargetType::kIndividual;
    const std::vector<uint8_t> launchablePositions = {3, 2, 1};
    const std::vector<uint8_t> targetablePositions = {1, 2};
    const int32_t attackMod = 85;
    const int32_t damageMod = 15;
    const int32_t criticalChanceMod = 5;
};

}   // namespace skills
}   // namespace engine
