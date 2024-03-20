#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct Smite : public CombatSkill {
    Smite : CombatSkill{
    id = "smite";
    name = "Smite";
    level = 0;
    type = Type::kMelee;
    targetType = TargetType::kIndividual;
    launchablePositions = {2, 1};
    targetablePositions = {1, 2};
    attackMod = 85;
    damageMod = 0;
    criticalChanceMod = 0;
    }
};

}   // namespace skills
}   // namespace engine
