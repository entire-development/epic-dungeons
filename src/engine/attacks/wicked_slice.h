#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct WickedSlice : public CombatSkill {
    const std::string id = "wicked_slice";
    const std::string name = "Wicked Slice";
    const uint8_t level = 0;
    const Type type = Type::kMelee;
    const TargetType targetType = TargetType::kIndividual;
    const std::vector<uint8_t> launchablePositions = {3, 2, 1};
    const std::vector<uint8_t> targetablePositions = {1, 2};
    const float attackMod = 85;
    const float damageMod = 15;
    const float criticalChanceMod = 5;
};

}   // namespace skills
}   // namespace engine
