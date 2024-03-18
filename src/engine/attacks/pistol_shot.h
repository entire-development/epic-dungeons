#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct PistolShot : public CombatSkill {
    PistolShot() : CombatSkill() {
        id = "pistol_shot";
        name = "Pistol Shot";
        level = 0;
        type = Type::kRanged;
        targetType = TargetType::kIndividual;
        launchablePositions = {4, 3, 2};
        targetablePositions = {2, 3, 4};
        attackMod = 85;
        damageMod = -15;
        criticalChanceMod = 7.5f;
    }
};

}   // namespace skills
}   // namespace engine
