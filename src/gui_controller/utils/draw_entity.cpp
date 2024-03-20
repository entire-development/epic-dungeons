#include "engine/skill.h"
#include "gui_controller/utils.h"
#include "renderer/text.h"
#include "static_data/game_config.h"
#include "vector2d/vector2d.h"

namespace gui {
namespace utils {

const Vector2d getPosition(uint8_t position) {
    static const float space_left = 0.0f;
    static const float space_right = cfg::WINDOW_WIDTH * 0.95f;
    static const float space_width = space_right - space_left;
    static const float entities_bottom = cfg::WINDOW_HEIGHT * 9 / 12;
    static const float mid = (space_left + space_right) / 2;
    static const float team_width = space_width * 4.2 / 9;
    static const float team_spacing = team_width * 0.28;
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

void drawHealthBar(const std::shared_ptr<graphics::Renderer> &renderer, Vector2d postion, Vector2d size, float health,
                   float max_health, graphics::Color color = {255, 0, 0, 255}) {
    int32_t max_cells_count = max_health;
    int32_t cells_count = health;
    float cell_spacing = 2;
    float cell_width = size.x() / max_cells_count - cell_spacing;
    float cell_height = size.y();
    for (int i = 0; i < max_cells_count; i++) {
        float x = postion.x() + i * (cell_width + cell_spacing) + cell_spacing / 2;
        float y = postion.y();
        graphics::Color c = color;
        if (i >= cells_count) {
            c = {0, 0, 0, 255};
        }
        renderer->drawRec({x, y, cell_width, cell_height, c});
    }
}

void drawEntity(const std::shared_ptr<graphics::Renderer> &renderer,
                const std::shared_ptr<engine::entities::Entity> &entity, const uint8_t &position, bool is_selected,
                const float &animation_progress) {
    static std::shared_ptr<graphics::Animation> animation = graphics::Animation::load("heroes/highwayman/idle.gif");
    auto sprite = animation->getFrame();
    if (position <= 3)
        sprite->setFlip(false, false);
    else
        sprite->setFlip(true, false);

    sprite->setRotation(animation_progress * 360);
    Vector2d bottom_center = getPosition(position);
    static const float entity_width = cfg::WINDOW_WIDTH / (8);
    sprite->toSizeX(entity_width);
    const float entity_height = sprite->getSize().y();

    Vector2d size = {entity_width, entity_height};
    Vector2d top_left = bottom_center - Vector2d {size.x() / 2, size.y()};
    Vector2d bottom_left = top_left + Vector2d {0, size.y()};
    renderer->draw(*sprite, top_left.x(), top_left.y());
    graphics::Text name = graphics::Text(entity->getName(), "arial", 20).setStyle(sf::Text::Bold);
    graphics::Text health = graphics::Text("Health: " + std::to_string(entity->getHealth()), "arial", 20);

    float width = size.x();
    float name_offset = 0;
    float health_offset = 0;
    if (position <= 3) {
        name_offset = 0;
        health_offset = 0;
    } else {
        name_offset = width - name.getSize().x();
        health_offset = width - health.getSize().x();
    }

    renderer->draw(name, bottom_left.x() + name_offset, bottom_left.y());
    renderer->draw(health, bottom_left.x() + health_offset, bottom_left.y() + 20);
    if (is_selected) {
        Vector2d bottom_center = getPosition(position);
        renderer->draw(graphics::Text("/\\", "arial", 20).setStyle(sf::Text::Bold), bottom_center.x(),
                       bottom_center.y() + 40);
    }
    // renderer->drawRec({top_left.x(), top_left.y(), size.x(), size.y(), {0, 0, 0, 0}, -2, {255, 255, 255, 255}});
}
}   // namespace utils
}   // namespace gui
