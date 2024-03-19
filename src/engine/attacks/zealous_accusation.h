#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct ZealousAccusation : public CombatSkill {
    id = "zealous_accusation";
    name = "Zealous Accusatuion";
    level = 0;
    type = Type::kRanged;
    targetType = TargetType::kIndividual;
    launchablePositions = {2, 1};
    targetablePositions = {1, 2};
    attackMod = 85;
    damageMod = -40;
    criticalChanceMod = -4;
};

}   // namespace skills
}   // namespace engine
