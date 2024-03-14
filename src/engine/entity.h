#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace engine {
namespace skills {
struct Skill;
}   // namespace skills

namespace items {
struct Weapon;
struct Armor;
}   // namespace items

namespace entities {
struct Stats {
    int32_t max_health = 20;
    int32_t defense = 0;
    int32_t protection = 0;
    int32_t speed = 0;
    int32_t min_damage = 0;
    int32_t max_damage = 0;
    int32_t critical_chance = 0;
    int32_t attack = 0;
};

struct Resistances {
    int32_t stun = 30;   // 30% chance to resist
    int32_t poison = 30;
    int32_t bleed = 30;
    int32_t disease = 30;
    int32_t move = 30;
    int32_t debuff = 30;
    int32_t death_blow = 67;
    int32_t trap = 40;
};

class Entity : public std::enable_shared_from_this<Entity> {
public:
    Entity(const std::string &name) : m_name(name) {}

    virtual ~Entity() {}

    uint32_t getHealth() const {
        return m_health;
    }

    uint32_t getMaxHealth() const {
        return m_max_health;
    }

    const bool isAlive() const {
        return m_is_alive;
    }

    void setWeapon(std::shared_ptr<items::Weapon> weapon) {
        m_weapon = weapon;
    }

    void setArmor(std::shared_ptr<items::Armor> armor) {
        m_armor = armor;
    }

    template<typename skill>
    void addSkill() {
        m_skills.push_back(std::make_shared<skill>());
    }

    // virtual skills::AttackResult takeAttack(std::shared_ptr<Entity> attacker, std::shared_ptr<skills::Attack> attack);

    uint8_t getPosition() const {
        return 0;
    }

    std::string getName() const {
        return m_name;
    }

protected:
    std::string m_name;
    bool m_is_alive = true;
    uint32_t m_max_health = 20;
    uint32_t m_health = 20;
    std::shared_ptr<items::Weapon> m_weapon = nullptr;
    std::shared_ptr<items::Armor> m_armor = nullptr;
    std::vector<std::shared_ptr<skills::Skill>> m_skills;
    Resistances m_resistances;
};

class Party {
public:
    Party() : m_members() {
        m_members.reserve(4);   // 4 is the max party size
    }

    void addMember(std::shared_ptr<Entity> member) {
        m_members.push_back(member);
    }

    std::shared_ptr<Entity> getMember(uint8_t index) {
        return m_members[index];
    }

    std::vector<std::shared_ptr<Entity>> getMembers() {
        return m_members;
    }

    uint8_t getMembersCount() {
        return m_members.size();
    }

    uint8_t getMemberPosition(std::shared_ptr<Entity> member) {
        for (uint8_t i = 0; i < m_members.size(); i++) {
            if (m_members[i] == member) {
                return i;
            }
        }
        return 0;
    }

protected:
    std::vector<std::shared_ptr<Entity>> m_members;
};

}   // namespace entities
}   // namespace engine
