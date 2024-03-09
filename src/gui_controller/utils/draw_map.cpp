
#include "gui_controller/utils.h"
#include <map>

namespace gui {
namespace utils {

void drawMap(const std::shared_ptr<graphics::Renderer> &renderer, const std::shared_ptr<dungeon::Dungeon> &dungeon,
             const Vector2d &center) {
    // load static textures
    const std::string map_path = "map/";
    static bool is_loaded = false;
    static std::map<dungeon::CellType, std::shared_ptr<graphics::Sprite>> m_hall_sprites;
    static std::map<dungeon::CellType, std::shared_ptr<graphics::Sprite>> m_room_sprites;
    static std::shared_ptr<graphics::Sprite> m_visited_room_sprite;
    static std::shared_ptr<graphics::Sprite> m_not_visited_room_sprite;
    static std::shared_ptr<graphics::Sprite> m_not_visited_hall_sprite;
    static std::shared_ptr<graphics::Sprite> m_selected_room_sprite;
    static std::shared_ptr<graphics::Sprite> m_current_cell_sprite;
    if (!is_loaded) {
        printf("Loading map textures\n");
        m_hall_sprites = {
            {dungeon::CellType::NOTHING, std::make_shared<graphics::Sprite>(map_path + "hall/clear.png")},
            {dungeon::CellType::FIGHT, std::make_shared<graphics::Sprite>(map_path + "hall/battle.png")},
            {dungeon::CellType::TREASURE, std::make_shared<graphics::Sprite>(map_path + "hall/curio.png")},
            {dungeon::CellType::TRAP, std::make_shared<graphics::Sprite>(map_path + "hall/trap.png")},
        };
        m_room_sprites = {
            {dungeon::CellType::NOTHING, std::make_shared<graphics::Sprite>(map_path + "room/empty.png")},
            {dungeon::CellType::FIGHT, std::make_shared<graphics::Sprite>(map_path + "room/battle.png")},
            {dungeon::CellType::BOSS, std::make_shared<graphics::Sprite>(map_path + "room/boss.png")},
            {dungeon::CellType::TREASURE, std::make_shared<graphics::Sprite>(map_path + "room/treasure.png")},
        };
        m_visited_room_sprite = std::make_shared<graphics::Sprite>(map_path + "room/marker_visited.png");
        m_not_visited_room_sprite = std::make_shared<graphics::Sprite>(map_path + "room/unknown.png");
        m_not_visited_hall_sprite = std::make_shared<graphics::Sprite>(map_path + "hall/dark.png");
        m_selected_room_sprite = std::make_shared<graphics::Sprite>(map_path + "room/marker_moving.png");
        m_current_cell_sprite = std::make_shared<graphics::Sprite>(map_path + "indicator.png");
        is_loaded = true;
    }
    std::shared_ptr<graphics::Renderer> r = renderer;
    std::shared_ptr<dungeon::Dungeon> d = dungeon;

    std::vector<std::shared_ptr<dungeon::Cell>> cells = d->getCells();
    std::shared_ptr<dungeon::Cell> current = d->getCurrentCell().lock();
    std::shared_ptr<dungeon::Room> m_target_room = d->getTargetRoom().lock();

    float cx = static_cast<float>(current->getPosition().first) * cfg::CELL_SIZE;
    float cy = static_cast<float>(current->getPosition().second) * cfg::CELL_SIZE;
    float x_offset = cx - center.x();
    float y_offset = cy - center.y();
    cx -= x_offset;
    cy -= y_offset;

    for (auto cell : cells) {
        float x = static_cast<float>(cell->getPosition().first) * cfg::CELL_SIZE - x_offset;
        float y = static_cast<float>(cell->getPosition().second) * cfg::CELL_SIZE - y_offset;
        float w = cfg::CELL_SIZE;
        std::shared_ptr<graphics::Sprite> base_sprite = nullptr;
        std::shared_ptr<graphics::Sprite> marker_sprite = nullptr;

        if (cell->isRoom()) {
            x -= cfg::CELL_SIZE;
            y -= cfg::CELL_SIZE;
            w = cfg::CELL_SIZE * 3;
            base_sprite = m_room_sprites[cell->getType()];
            if (cell->isVisited()) {
                marker_sprite = m_visited_room_sprite;
            } else {
                base_sprite = m_not_visited_room_sprite;
            }
        } else {
            base_sprite = m_hall_sprites[cell->getType()];
            if (!cell->isVisited()) {
                base_sprite = m_not_visited_hall_sprite;
            }
        }
        base_sprite->toSize(w, w);
        float alpha_distance = (cx - x) * (cx - x) + (cy - y) * (cy - y);
        alpha_distance = 1 - alpha_distance / (cfg::CELL_SIZE * cfg::CELL_SIZE * 168);
        alpha_distance *= 255;
        alpha_distance = std::max(0, std::min(255, static_cast<int>(alpha_distance)));
        base_sprite->setColor({255, 255, 255, (uint8_t) alpha_distance});
        r->draw(*base_sprite, x, y);
        if (marker_sprite) {
            marker_sprite->toSize(w, w);
            marker_sprite->setColor({255, 255, 255, (uint8_t) alpha_distance});
            r->draw(*marker_sprite, x, y);
        }
        if (cell == current) {
            m_current_cell_sprite->toSize(w, w);
            r->draw(*m_current_cell_sprite, x, y);
        }
        if (cell == m_target_room) {
            m_selected_room_sprite->toSize(w, w);
            r->draw(*m_selected_room_sprite, x, y);
        }
    }
}
}   // namespace utils
}   // namespace gui