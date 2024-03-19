#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct SniperShot : public CombatSkill {
    id = "sniper_shot";
    name = "Sniper Shot";
    level = 0;
    type = Type::kRanged;
    targetType = TargetType::kIndividual;
    launchablePositions = {4, 3};
    targetablePositions = {2, 3, 4};
    attackMod = 95;
    damageMod = 0;
    criticalChanceMod = 5;
};

}   // namespace skills
}   // namespace engine
