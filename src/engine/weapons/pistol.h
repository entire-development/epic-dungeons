#pragma once
#include <engine/attacks/melee.h>
#include <engine/attacks/pistol_shot.h>
#include <engine/weapon.h>
#include <memory>

namespace engine {
namespace items {

class Pistol : public Weapon {
public:
    Pistol() : Weapon() {
        m_attack = std::make_shared<actions::PistolShot>();
        m_secondary_attack = std::make_shared<actions::Melee>();
    }
};

}   // namespace items
}   // namespace engine
