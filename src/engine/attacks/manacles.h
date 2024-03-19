#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct Manacles : public CombatSkill {
    id = "manacles";
    name = "Manacles";
    level = 0;
    type = Type::kRanged;
    targetType = TargetType::kIndividual;
    launchablePositions = {3, 2};
    targetablePositions = {1, 2, 3};
    attackMod = 95;
    damageMod = -60;
    criticalChanceMod = 1;
};

}   // namespace skills
}   // namespace engine
