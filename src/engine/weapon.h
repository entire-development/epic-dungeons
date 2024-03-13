#pragma once
#include <memory>

namespace engine {
namespace entities {}   // namespace entities

namespace actions {
class Attack;
}   // namespace actions

namespace items {
class Weapon {
public:
    Weapon() : m_attack(nullptr), m_secondary_attack(nullptr) {}

    std::shared_ptr<actions::Attack> geAttack() {
        return m_attack;
    }

    std::shared_ptr<actions::Attack> getSecondaryAttack() {
        return m_secondary_attack;
    }

protected:
    std::shared_ptr<actions::Attack> m_attack;
    std::shared_ptr<actions::Attack> m_secondary_attack;
};
}   // namespace items
}   // namespace engine