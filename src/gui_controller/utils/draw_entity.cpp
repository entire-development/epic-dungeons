#include "engine/engine.h"
#include "engine/skill.h"
#include "gui_controller/utils.h"
#include "gui_controller/views/hero.h"
#include "logging/logger.h"
#include "renderer/text.h"
#include "static_data/game_config.h"
#include "vector2d/vector2d.h"

namespace gui {
namespace utils {

void drawEntity(const std::shared_ptr<graphics::Renderer> &renderer,
                const std::shared_ptr<engine::entities::Entity> &entity, const uint8_t &position, bool is_selected,
                const float &animation_progress) {
    auto view = std::make_shared<views::Entity>(entity);
    view->setSelection(is_selected ? views::Entity::Selection::kSelected : views::Entity::Selection::kNone);

    view->render(renderer, position, animation_progress);
}
}   // namespace utils
}   // namespace gui
