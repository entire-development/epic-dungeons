#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct Pick : public CombatSkill {
    Pick : CombatSkill() {
    id = "pick";
    name = "Pick";
    level = 0;
    type = Type::kMelee;
    targetType = TargetType::kIndividual;
    launchablePositions = {3, 2, 1};
    targetablePositions = {1, 2};
    attackMod = 90;
    damageMod = -15;
    criticalChanceMod = 1;
    }
};

}   // namespace skills
}   // namespace engine
