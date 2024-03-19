#pragma once

#include "engine/armor/highwayman.h"
#include "engine/attacks/pistol_shot.h"
#include "engine/attacks/wicked_slice.h"

#include "engine/weapons/pistol.h"
#include "hero.h"

namespace engine {
namespace entities {

class Highwayman : public Hero {
public:
    Highwayman() : Hero("Highwayman") {
        m_health = 23;
        m_max_health = 23;
        m_weapon = std::make_shared<items::Pistol>();
        m_armor = std::make_shared<items::HighwaymanArmor>();
        addSkill<skills::PistolShot>();
        addSkill<skills::WickedSlice>();
    }
};

}   // namespace entities
}   // namespace engine
