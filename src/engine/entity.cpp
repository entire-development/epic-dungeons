#include "entity.h"
#include "action.h"
#include "attacks/attack.h"
#include "weapon.h"

namespace engine {
namespace entities {
actions::AttackReuslt Entity::takeAttack(std::shared_ptr<Entity> attacker, std::shared_ptr<actions::Attack> attack) {
    actions::AttackReuslt result;
    if (attack->getChanceToHit(attacker, shared_from_this()) > rand() % 100) {
        result.type = actions::AttackReuslt::Type::kHit;
        int32_t min_damage = attack->getMinDamage(attacker, shared_from_this());
        int32_t max_damage = attack->getMaxDamage(attacker, shared_from_this());
        int32_t damage = min_damage + rand() % (max_damage - min_damage + 1);
        if (attack->getCriticalChance(attacker, shared_from_this()) > rand() % 100) {
            damage *= 1.5;
            result.type = actions::AttackReuslt::Type::kCritical;
        }
        result.damage = damage;
    } else {
        result.type = actions::AttackReuslt::Type::kMiss;
    }
    return result;
}

}   // namespace entities
}   // namespace engine