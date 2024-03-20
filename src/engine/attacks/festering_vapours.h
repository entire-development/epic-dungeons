#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct FesteringVapours : public CombatSkill {
    FesteringVapours() : CombatSkill() {
    id = "festering_vapours";
    name = "Festering Vapours";
    level = 0;
    type = Type::kRanged;
    targetType = TargetType::kIndividual;
    launchablePositions = {4, 3, 2, 1};
    targetablePositions = {1, 2, 3, 4};
    attackMod = 95;
    damageMod = -75;
    criticalChanceMod = 0;
    }
};

}   // namespace skills
}   // namespace engine
