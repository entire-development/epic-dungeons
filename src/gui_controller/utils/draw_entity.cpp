#include "gui_controller/utils.h"
#include "static_data/game_config.h"
#include "vector2d/vector2d.h"

namespace gui {
namespace utils {

const Vector2d getPosition(uint8_t position) {
    static const float space_left = 0.0f;
    static const float space_right = cfg::WINDOW_WIDTH * 0.9f;
    static const float space_width = space_right - space_left;
    static const float entities_bottom = cfg::WINDOW_HEIGHT * 9 / 12;
    static const float mid = (space_left + space_right) / 2;
    static const float team_width = space_width * 4.2 / 9;
    static const float team_spacing = team_width / 4;
    static const float team_mid_offset = team_width * 1.5 / 10;

    static std::vector<Vector2d> positions = {
        {mid - team_mid_offset - team_spacing * 3, entities_bottom},
        {mid - team_mid_offset - team_spacing * 2, entities_bottom},
        {mid - team_mid_offset - team_spacing * 1, entities_bottom},
        {mid - team_mid_offset - team_spacing * 0, entities_bottom},
        {mid + team_mid_offset + team_spacing * 0, entities_bottom},
        {mid + team_mid_offset + team_spacing * 1, entities_bottom},
        {mid + team_mid_offset + team_spacing * 2, entities_bottom},
        {mid + team_mid_offset + team_spacing * 3, entities_bottom},
    };
    return positions[position];
};

void drawEntity(const std::shared_ptr<graphics::Renderer> &renderer,
                const std::shared_ptr<engine::entities::Entity> &entity, const uint8_t &position,
                const float &animation_progress) {
    static std::shared_ptr<graphics::Sprite> sprite = std::make_shared<graphics::Sprite>("heroes/gangster.png");
    float anim = animation_progress * 4 - (3 - position);
    anim = anim < 0 ? 0 : (anim > 1 ? 1 : anim);
    sprite->setRotation(anim * 360);

    Vector2d bottom_center = getPosition(position);
    static const float entity_width = cfg::WINDOW_WIDTH / (8);
    sprite->toSizeX(entity_width);
    const float entity_height = sprite->getSize().y();

    Vector2d size = {entity_width, entity_height};
    Vector2d top_left = bottom_center - Vector2d {size.x() / 2, size.y()};
    // top_left = top_left - Vector2d {0, size.y() * static_cast<float>(sin(anim * M_PI) / 2)};
    renderer->draw(*sprite, top_left.x(), top_left.y());
}
}   // namespace utils
}   // namespace gui