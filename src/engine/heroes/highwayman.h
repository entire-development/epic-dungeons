#pragma once

#include "engine/weapons/pistol.h"
#include "hero.h"

namespace engine {
namespace entities {

class Highwayman : public Hero {
public:
    Highwayman() : Hero("Highwayman") {
        m_health = 23;
        m_max_health = 23;
        
    }
};

}   // namespace entities
}   // namespace engine