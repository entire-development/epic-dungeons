#include "hero.h"
#include "logging/logger.h"

namespace gui {
namespace views {

static std::map<std::string, std::shared_ptr<graphics::Animation>> animations;
static std::map<std::string, std::shared_ptr<graphics::Sprite>> sprites;

static std::shared_ptr<graphics::Animation> getAnimation(const std::string &path) {
    if (animations.find(path) == animations.end()) {
        animations[path] = std::make_shared<graphics::Animation>(path);
    }
    return animations[path];
}

static std::shared_ptr<graphics::Sprite> getSprite(const std::string &path) {
    if (sprites.find(path) == sprites.end()) {
        sprites[path] = std::make_shared<graphics::Sprite>(path);
    }
    return sprites[path];
}

const Vector2d getPosition(uint8_t position) {
    static const float space_left = 0.0f;
    static const float space_right = cfg::WINDOW_WIDTH * 0.95f;
    static const float space_width = space_right - space_left;
    static const float entities_bottom = cfg::WINDOW_HEIGHT * 9 / 12;
    static const float mid = (space_left + space_right) / 2;
    static const float team_width = space_width * 4.2 / 9;
    static const float team_spacing = team_width * 0.28;
    static const float team_mid_offset = team_width * 1.7 / 10;

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

const void Entity::render(const std::shared_ptr<graphics::Renderer> &renderer, const uint8_t &position,
                          const float &animation_progress) {
    auto entity = m_entity.lock();
    std::shared_ptr<graphics::Sprite> sprite;
    float dh = 0;
    if (entity->isAlive()) {
        sprite = m_animations[m_state]->getFrame();
        sprite->setScale(1);
        sprite->setRotation(animation_progress * 360);
    } else {
        sprite = m_grave;
        sprite->setScale(0.32);
        dh = sin(animation_progress * 3.14) * 15;
    }
    if (position <= 3)
        sprite->setFlip(false, false);
    else
        sprite->setFlip(true, false);

    Vector2d bottom_center = getPosition(position);
    static const float entity_width = cfg::WINDOW_WIDTH / (8);
    const float entity_height = sprite->getSize().y();

    Vector2d size = {entity_width, entity_height};
    Vector2d top_left = bottom_center - Vector2d {size.x() / 2, size.y()};
    Vector2d bottom_left = top_left + Vector2d {0, size.y()};
    // if (entity->isAlive())
    // sprite->setColor("#ffffff");
    // else
    // sprite->setColor("#ff0000");
    renderer->draw(*sprite, top_left.x(), top_left.y() - dh);
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
    if (m_selection == Selection::kSelected) {
        Vector2d bottom_center = getPosition(position);
        renderer->draw(graphics::Text("/\\", "arial", 20).setStyle(sf::Text::Bold).setColor("#00ff00"),
                       bottom_center.x(), bottom_center.y() + 40);
    }
    if (m_selection == Selection::kTarget) {
        Vector2d bottom_center = getPosition(position);
        renderer->draw(graphics::Text("/\\", "arial", 20).setStyle(sf::Text::Bold).setColor("#ff0000"),
                       bottom_center.x(), bottom_center.y() + 40);
    }
    if (m_selection == Selection::kSelectable) {
        Vector2d bottom_center = getPosition(position);
        renderer->draw(graphics::Text("X", "arial", 20).setStyle(sf::Text::Bold).setColor("#999999"), bottom_center.x(),
                       bottom_center.y() + 40);
    }
    if (m_selection == Selection::kTargetable) {
        Vector2d bottom_center = getPosition(position);
        renderer->draw(graphics::Text("X", "arial", 20).setStyle(sf::Text::Bold).setColor("#999999"), bottom_center.x(),
                       bottom_center.y() + 40);
    }
    if (m_selection == Selection::kNotSelectable) {
        Vector2d bottom_center = getPosition(position);
        renderer->draw(graphics::Text("X", "arial", 20).setStyle(sf::Text::Bold).setColor("#000000"), bottom_center.x(),
                       bottom_center.y() + 40);
    }
    if (m_selection == Selection::kNotTargetable) {
        Vector2d bottom_center = getPosition(position);
        renderer->draw(graphics::Text("X", "arial", 20).setStyle(sf::Text::Bold).setColor("#000000"), bottom_center.x(),
                       bottom_center.y() + 40);
    }
}

void Entity::bind(const std::shared_ptr<engine::entities::Entity> &entity) {
    m_entity = entity;
    std::string path = "heroes/" + entity->getId();
    m_animations[State::kIdle] = getAnimation(path + "/idle.gif");
    m_animations[State::kCombat] = getAnimation(path + "/combat.gif");
    m_portrait = getSprite(path + "/portrait.png");
    m_grave = getSprite("heroes/grave.png");
    m_grave->setScale(0.32);
}

}   // namespace views
}   // namespace gui
