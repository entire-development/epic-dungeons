#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace engine {
namespace actions {
class Action;
class Attack;
struct AttackReuslt;
}   // namespace actions

namespace items {
class Weapon;
}   // namespace items

namespace entities {
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

    virtual actions::AttackReuslt takeAttack(std::shared_ptr<Entity> attacker, std::shared_ptr<actions::Attack> attack);

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
