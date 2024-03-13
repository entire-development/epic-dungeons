#pragma once

#include "engine/entity.h"
#include <memory>

namespace engine {
namespace entities {
class Hero : public Entity {
public:
    Hero(const std::string &name) : Entity(name) {}
};
}   // namespace entities
}   // namespace engine