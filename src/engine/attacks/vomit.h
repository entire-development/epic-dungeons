#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct Vomit : public CombatSkill {
    id = "vomit";
    name = "Vomit";
    level = 0;
    type = Type::kRangee;
    targetType = TargetType::kIndividual;
    launchablePositions = {3, 2};
    targetablePositions = {2, 3};
    attackMod = 95;
    damageMod = -90;
    criticalChanceMod = 2;
};

}   // namespace skills
}   // namespace engine
