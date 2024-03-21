#pragma once
#include "engine/skill.h"

namespace engine {
namespace skills {
struct WickedSlice : public CombatSkill {
    WickedSlice() : CombatSkill() {
        id = "wicked_slice";
        name = "Wicked Slice";
        level = 0;
        type = Type::kMelee;
        targetType = TargetType::kIndividual;
        launchablePositions = {3, 2, 1};
        targetablePositions = {1, 2};
        attackMod = 85;
        damageMod = 15;
        criticalChanceMod = 5;
    }
};

}   // namespace skills
}   // namespace engine
