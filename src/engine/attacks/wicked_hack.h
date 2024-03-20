#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct WickedHack : public CombatSkill {
    WickedHack : CombatSkill() {
    id = "wicked_hack";
    name = "Wicked Hack";
    level = 0;
    type = Type::kMelee;
    targetType = TargetType::kIndividual;
    launchablePositions = {2, 1};
    targetablePositions = {1, 2};
    attackMod = 85;
    damageMod = 0;
    criticalChanceMod = 4;
    }
};

}   // namespace skills
}   // namespace engine
