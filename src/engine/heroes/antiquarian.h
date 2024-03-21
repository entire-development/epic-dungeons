#pragma once
#include "hero.h"

#include "engine/armor/antiquarian.h"
#include "engine/weapons/makeshift_censer.h"

#include "engine/attacks/festering_vapours.h"
#include "engine/attacks/kris_stab.h"

namespace engine {
namespace entities {

class Antiquarian : public Hero {
public:
    Antiquarian() : Hero() {
        m_id = "antiquarian";
        m_name = "Antiquarian";
        m_health = 17;
        m_max_health = 17;
        m_weapon = std::make_shared<items::MakeshiftCenser>();
        m_armor = std::make_shared<items::AntiquarianArmor>();
        addSkill<skills::KrisStab>();
        addSkill<skills::FesteringVapours>();
    }
};

}   // namespace entities
}   // namespace engine
