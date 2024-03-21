#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct TargetTag : public CombatSkill {
    TargetTag() : CombatSkill() {
        id = "target_tag";
        name = "Target Tag";
        level = 0;
        type = Type::kRanged;
        targetType = TargetType::kIndividual;
        launchablePositions = {4, 3, 2, 1};
        targetablePositions = {1, 2, 3, 4};
        attackMod = 100;
        damageMod = -100;
        criticalChanceMod = 0;
    }
};

}   // namespace skills
}   // namespace engine
