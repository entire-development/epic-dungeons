#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct IronSwan : public CombatSkill {
    IronSwan : CombatSkill() {
    id = "iron_swan";
    name = "Iron Swan";
    level = 0;
    type = Type::kMelee;
    targetType = TargetType::kIndividual;
    launchablePositions = {1};
    targetablePositions = {4};
    attackMod = 85;
    damageMod = 0;
    criticalChanceMod = 5;
    }
};

}   // namespace skills
}   // namespace engine
