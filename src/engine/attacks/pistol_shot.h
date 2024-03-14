#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct PistolShot : public CombatSkill {
    const std::string id = "pistol_shot";
    const uint8_t level = 0;
    const Type type = Type::kRanged;
    const TargetType targetType = TargetType::kIndividual;
    const std::vector<uint8_t> launchablePositions = {4, 3, 2};
    const std::vector<uint8_t> targetablePositions = {2, 3, 4};
    const int32_t attackMod = 85;
    const int32_t damageMod = -15;
    const int32_t criticalChanceMod = 7.5;
};

}   // namespace skills
}   // namespace engine
