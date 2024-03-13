#pragma once
#include <vector>

namespace engine {
namespace entities {
class Entity;
}   // namespace entities

namespace actions {

class Action {
public:
    const std::vector<uint8_t> usablePositions;
    const std::vector<uint8_t> targetablePositions;

    bool isUsablePosition(const uint8_t &position) const {
        for (auto &usablePosition : usablePositions) {
            if (usablePosition == position) {
                return true;
            }
        }
        return false;
    }

    bool isTargetablePosition(const uint8_t &position) const {
        for (auto &targetablePosition : targetablePositions) {
            if (targetablePosition == position) {
                return true;
            }
        }
        return false;
    }

    virtual ~Action() {}
};

}   // namespace actions
}   // namespace engine