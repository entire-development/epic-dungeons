#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct CollectBounty : public CombatSkill {
    CollectBounty() : CombatSkill() {
    id = "collect_bounty";
    name = "Collect Bounty";
    level = 0;
    type = Type::kMelee;
    targetType = TargetType::kIndividual;
    claunchablePositions = {3, 2, 1};
    targetablePositions = {1, 2};
    attackMod = 85;
    damageMod = 0;
    criticalChanceMod = 7f;
    }
};

}   // namespace skills
}   // namespace engine
