#pragma once

#include "engine/weapons/pistol.h"
#include "hero.h"

namespace engine {
namespace entities {

class Gangster : public Hero {
public:
    Gangster() : Hero("Lamar") {
        m_health = 20;
        m_max_health = 20;
        setWeapon(std::make_shared<items::Pistol>());
    }
};

}   // namespace entities
}   // namespace engine