#pragma once
#include "engine/action.h"
#include "engine/entity.h"

namespace engine {
namespace actions {

struct AttackReuslt {
    enum class Type {
        kMiss,
        kHit,
        kCritical,
    } type;
    int32_t damage;
};

class Attack : public Action {
public:
    const std::vector<uint8_t> usablePositions;
    const std::vector<uint8_t> targetablePositions;

    virtual int32_t getMinDamage(std::shared_ptr<entities::Entity> actor,
                                 std::shared_ptr<entities::Entity> target) const {
        return m_min_damage;
    }

    virtual int32_t getMaxDamage(std::shared_ptr<entities::Entity> actor,
                                 std::shared_ptr<entities::Entity> target) const {
        return m_max_damage;
    }

    virtual int32_t getChanceToHit(std::shared_ptr<entities::Entity> actor,
                                   std::shared_ptr<entities::Entity> target) const {
        return m_accuracy;
    }

    virtual int32_t getCriticalChance(std::shared_ptr<entities::Entity> actor,
                                      std::shared_ptr<entities::Entity> target) const {
        return m_critical_chance;
    }

protected:
    int32_t m_min_damage;
    int32_t m_max_damage;
    int32_t m_accuracy;
    int32_t m_critical_chance;
};

}   // namespace actions
}   // namespace engine
