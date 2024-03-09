#pragma once
#include "dungeon/dungeon.h"
#include "renderer/graphics.h"
#include "vector2d/vector2d.h"
#include <memory>

namespace gui {
namespace utils {
void drawMap(const std::shared_ptr<graphics::Renderer> &renderer, const std::shared_ptr<dungeon::Dungeon> &dungeon,
             const Vector2d &center);

}   // namespace utils
}   // namespace gui