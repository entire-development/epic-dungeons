#pragma once
#include <string>
#include <vector>

namespace engine {

namespace skills {

enum class Type {
    kMelee,
    kRanged,
    kMove,
};

enum class TargetType {
    kIndividual,
    kParty,
    kOtherParty,
};

struct Skill {
    virtual ~Skill() = default;

    const std::string id;
    const std::string name;
    const uint8_t level = 0;
    const Type type = Type::kMelee;
    const TargetType targetType = TargetType::kIndividual;
    const std::vector<uint8_t> launchablePositions;
    const std::vector<uint8_t> targetablePositions;

    bool isUsable(const uint8_t position) const {
        return std::find(launchablePositions.begin(), launchablePositions.end(), position) != launchablePositions.end();
    }

    bool isTargetable(const uint8_t position) const {
        return std::find(targetablePositions.begin(), targetablePositions.end(), position) != targetablePositions.end();
    }
};

struct Move : public Skill {
    const std::string id = "move";
    const std::string name = "Move";
    const Type type = Type::kMove;
    const TargetType targetType = TargetType::kIndividual;

    uint8_t distance = 0;
};

struct CombatSkill : public Skill {
    const float damageMod = 0;
    const float attackMod = 0;
    const float criticalChanceMod = 0;
};

struct AttackResult {
    bool isHit = false;
    bool isCritical = false;
    int32_t damage = 0;
};

}   // namespace skills
}   // namespace engine