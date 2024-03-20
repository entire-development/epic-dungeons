#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct SuppresingFire : public CombatSkill {
    SuppresingFire : CombatSkill {
    id = "suppresing_fire";
    name = "Suppresing Fire";
    level = 0;
    type = Type::kRanged;
    targetType = TargetType::kIndividual;
    launchablePositions = {4, 3};
    targetablePositions = {3, 4};
    attackMod = 95;
    damageMod = -80;
    criticalChanceMod = -10;
    }
};

}   // namespace skills
}   // namespace engine
