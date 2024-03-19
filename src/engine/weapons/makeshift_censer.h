#pragma once
#include "engine/item.h"
#include <memory>

namespace engine {
namespace items {

struct MakeshiftCencser : public Weapon {
    id = "makeshift_censer";
    name = "Makeshift Censer";
    attackMod = 0;
    minDamage = 3;
    maxDamage = 5;
    criticalChanceMod = 1;
    speedMod = 5;
};

}   // namespace items
}   // namespace engine
