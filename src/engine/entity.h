#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace engine {
namespace skills {
struct Skill;
struct AttackResult;
struct CombatSkill;
}   // namespace skills

namespace items {
struct Weapon;
struct Armor;
}   // namespace items

namespace entities {
class Party;

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
    friend class Party;

public:
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

    void setWeapon(const std::shared_ptr<items::Weapon> &weapon) {
        m_weapon = weapon;
    }

    const std::shared_ptr<items::Weapon> &getWeapon() const {
        return m_weapon;
    }

    void setArmor(const std::shared_ptr<items::Armor> &armor) {
        m_armor = armor;
    }

    const std::shared_ptr<items::Armor> &getArmor() const {
        return m_armor;
    }

    void updateHealth(const int32_t &amount);

    template<typename skill>
    void addSkill() {
        m_skills.push_back(std::make_shared<skill>());
    }

    const std::vector<std::shared_ptr<skills::Skill>> &getSkills() {
        return m_skills;
    }

    virtual const skills::AttackResult takeAttack(const std::shared_ptr<Entity> &attacker,
                                                  const std::shared_ptr<skills::CombatSkill> &skill);

    virtual const int32_t calculateHitChance(const std::shared_ptr<Entity> &target,
                                             const std::shared_ptr<skills::CombatSkill> &skill) const;

    virtual const int32_t calculateCritChance(const std::shared_ptr<skills::CombatSkill> &skill) const;

    virtual const int32_t calculateDamage(const std::shared_ptr<skills::CombatSkill> &skill) const;

    const int32_t getSpeed() const;

    const uint8_t getPosition() const;

    const std::string &getId() const {
        return m_id;
    }

    const std::string &getName() const {
        return m_name;
    }

    const Resistances &getResistances() const {
        return m_resistances;
    }

    const std::shared_ptr<Party> getParty() const {
        return m_party.lock();
    }

protected:
    std::string m_id;
    std::string m_name;
    bool m_is_alive = true;
    int32_t m_max_health = 20;
    int32_t m_health = 20;
    std::shared_ptr<items::Weapon> m_weapon = nullptr;
    std::shared_ptr<items::Armor> m_armor = nullptr;
    std::vector<std::shared_ptr<skills::Skill>> m_skills;
    Resistances m_resistances;
    std::weak_ptr<Party> m_party;
};

class Party : public std::enable_shared_from_this<Party> {
public:
    Party() : m_members() {
        m_members.reserve(4);   // 4 is the max party size
    }

    void addMember(const std::shared_ptr<Entity> &member) {
        if (m_members.size() == 4) {
            throw std::runtime_error("Party is full");
            return;
        }
        if (member->m_party.lock() != nullptr) {
            throw std::runtime_error("Entity is already in a party");
            return;
        }
        member->m_party = shared_from_this();
        m_members.push_back(member);
    }

    void removeMember(const std::shared_ptr<Entity> &member) {
        auto it = std::ranges::find(m_members.begin(), m_members.end(), member);
        if (it != m_members.end()) {
            m_members.erase(it);
            member->m_party.reset();
        }
    }

    std::shared_ptr<Entity> getMember(const uint8_t &index) {
        if (index < m_members.size()) {
            return m_members[index];
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<Entity>> getMembers() {
        return m_members;
    }

    uint8_t getMembersCount() {
        return m_members.size();
    }

    uint8_t getAliveMembersCount() {
        uint8_t count = 0;
        for (auto &member : m_members) {
            if (member->isAlive()) {
                count++;
            }
        }
        return count;
    }

    uint8_t getMemberPosition(const std::shared_ptr<const Entity> &member) {
        for (uint8_t i = 0; i < m_members.size(); i++) {
            if (m_members[i] == member) {
                return i;
            }
        }
        return 0;
    }

    void swapMembers(const uint8_t &index1, const uint8_t &index2) {
        if (index1 < m_members.size() && index2 < m_members.size()) {
            std::swap(m_members[index1], m_members[index2]);
        } else {
            throw std::runtime_error("Index out of range");
        }
    }

    void arrangeMembers() {
        // move dead members to the end
        // bubble sort
        for (uint8_t i = 0; i < m_members.size(); i++) {
            while (i + 1 < m_members.size() && !m_members[i]->isAlive() && m_members[i + 1]->isAlive())
                swapMembers(i, i + 1);
        }
    }

    void clear() {
        for (auto &member : m_members) {
            member->m_party.reset();
        }
        m_members.clear();
    }

    void memberDied(const std::shared_ptr<Entity> &member) {
        arrangeMembers();
        // removeMember(member);
    }

protected:
    std::vector<std::shared_ptr<Entity>> m_members;
};

}   // namespace entities
}   // namespace engine
