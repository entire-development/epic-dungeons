#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct KrisStab : public CombatSkill {
    KrisStab() : CombatSkill() {
    id = "kris_stab";
    name = "Kris Stab";
    level = 0;
    type = Type::kMelee;
    targetType = TargetType::kIndividual;
    launchablePositions = {4, 3, 2, 1};
    targetablePositions = {1, 2, 3};
    attackMod = 85;
    damageMod = 0;
    criticalChanceMod = 3;
    }
};

}   // namespace skills
}   // namespace engine
