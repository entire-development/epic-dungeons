#pragma once
#include "dungeon/dungeon.h"
#include "engine/engine.h"
#include "engine/entity.h"
#include "renderer/graphics.h"
#include "vector2d/vector2d.h"
#include <memory>

namespace gui {
namespace utils {
void drawMap(const std::shared_ptr<graphics::Renderer> &renderer, const std::shared_ptr<dungeon::Dungeon> &dungeon,
             const Vector2d &center, const float &cell_size, const float &animation_progress = 0.0f);

void cellView(const std::shared_ptr<graphics::Renderer> &renderer, const std::shared_ptr<dungeon::Dungeon> &dungeon,
              const float &animation_progress = 0.0f);

void drawEntity(const std::shared_ptr<graphics::Renderer> &renderer,
                const std::shared_ptr<engine::entities::Entity> &entity, const uint8_t &position,
                const float &animation_progress = 0.0f);

void drawGUI(const std::shared_ptr<graphics::Renderer> &renderer, const std::shared_ptr<engine::Engine> &engine);

}   // namespace utils
}   // namespace gui