#include "entity.h"
#include "item.h"
#include "logging/logger.h"
#include "skill.h"

namespace engine {
namespace entities {

const int32_t Entity::calculateDamage(const std::shared_ptr<skills::CombatSkill> &skill) const {
    int32_t damage = 0;
    if (m_weapon) {
        damage = m_weapon->minDamage + (rand() % (m_weapon->maxDamage - m_weapon->minDamage + 1));
    }
    if (skill) {
        damage = (damage * (100 + skill->damageMod)) / 100;
    }
    return damage;
}

const int32_t Entity::calculateHitChance(const std::shared_ptr<entities::Entity> &target,
                                         const std::shared_ptr<skills::CombatSkill> &skill) const {
    int32_t hit_chance = 0;
    if (m_weapon)
        hit_chance += m_weapon->attackMod;
    if (skill)
        hit_chance += skill->attackMod;
    if (target->m_armor)
        hit_chance -= target->m_armor->defenseMod;

    return hit_chance;
}

const int32_t Entity::calculateCritChance(const std::shared_ptr<skills::CombatSkill> &skill) const {
    int32_t crit_chance = 0;
    if (m_weapon)
        crit_chance += m_weapon->criticalChanceMod;
    if (skill)
        crit_chance += skill->criticalChanceMod;

    return crit_chance;
}

const int32_t Entity::getSpeed() const {
    int32_t speed = 0;
    if (m_weapon)
        speed += m_weapon->speedMod;
    if (m_armor)
        speed += m_armor->speedMod;
    return speed;
}

const skills::AttackResult Entity::takeAttack(const std::shared_ptr<Entity> &attacker,
                                              const std::shared_ptr<skills::CombatSkill> &skill) {
    skills::AttackResult result;
    int32_t hit_chance = attacker->calculateHitChance(shared_from_this(), skill);
    if (rand() % 100 < hit_chance) {
        result.isHit = true;
        result.damage = attacker->calculateDamage(skill);
        if (rand() % 100 < attacker->calculateCritChance(skill)) {
            result.isCritical = true;
            result.damage *= 1.5;
        }
        if (rand() % 100 < m_armor->protectionMod) {
            result.damage = result.damage * (100 - m_armor->protectionMod) / 100;
        }
        logging::debug(attacker->getName() + " attacks " + getName() + " with " + skill->name);
        updateHealth(-result.damage);
    }
    return result;
}

const uint8_t Entity::getPosition() const {
    if (m_party.expired()) {
        return 0;
    }
    return m_party.lock()->getMemberPosition(shared_from_this());
}

void Entity::updateHealth(const int32_t &amount) {
    int32_t old_health = m_health;
    m_health += amount;
    if (m_health > m_max_health) {
        m_health = m_max_health;
    }
    if (m_health <= 0) {
        m_health = 0;
        m_is_alive = false;
        if (!m_party.expired()) {
            m_party.lock()->memberDied(shared_from_this());
        }
    }
    logging::debug(m_name + " health: " + std::to_string(old_health) + " -> " + std::to_string(m_health));
}

}   // namespace entities
}   // namespace engine
