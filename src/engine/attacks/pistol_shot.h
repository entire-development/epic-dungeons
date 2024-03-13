#pragma once
#include "attack.h"

namespace engine {
namespace actions {

class PistolShot : public Attack {
public:
    std::vector<uint8_t> usablePositions = {0, 1, 2, 3};
    std::vector<uint8_t> targetablePositions = {0, 1, 2, 3};

protected:
    int32_t m_min_damage = 3;
    int32_t m_max_damage = 6;
    int32_t m_accuracy = 80;
    int32_t m_critical_chance = 10;
};

}   // namespace actions
}   // namespace engine
