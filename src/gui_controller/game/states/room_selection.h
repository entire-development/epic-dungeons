#pragma once
#include "dungeon/dungeon.h"
#include "gui_controller/game/game_machine.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <map>
#include <memory>

namespace gui {
namespace game {
class RoomSelection : public GameState {
public:
    RoomSelection() : GameState(), m_hall_sprites(), m_room_sprites() {
        const std::string map_path = "map/";
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
    }

    virtual void enter(GameMachine *gm) {
        is_key_pressed = true;
        std::shared_ptr<dungeon::Dungeon> d = gm->m_engine.lock().get()->getDungeon();
        neighbours = d->getRoomNeighbours(std::dynamic_pointer_cast<dungeon::Room>(d->getCurrentCell().lock()));
        while (neighbours[r_selected].expired()) {
            r_selected = (r_selected + 1) % 4;
        }
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        render(r, d);
    }

    virtual void update(GameMachine *gm) {
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        std::shared_ptr<dungeon::Dungeon> d = gm->m_engine.lock().get()->getDungeon();
        bool pressed_up = keyboard::isPressed(keyboard::KEY_UP) || keyboard::isPressed(keyboard::KEY_W);
        bool pressed_down = keyboard::isPressed(keyboard::KEY_DOWN) || keyboard::isPressed(keyboard::KEY_S);
        bool pressed_right = keyboard::isPressed(keyboard::KEY_RIGHT) || keyboard::isPressed(keyboard::KEY_D);
        bool pressed_left = keyboard::isPressed(keyboard::KEY_LEFT) || keyboard::isPressed(keyboard::KEY_A);
        bool pressed_enter = keyboard::isPressed(keyboard::KEY_ENTER);

        if (!(pressed_right || pressed_left || pressed_enter || pressed_up || pressed_down))
            is_key_pressed = false;

        if (is_key_pressed)
            return;
        if (pressed_up && !neighbours[0].expired()) {
            is_key_pressed = true;
            r_selected = 0;
        } else if (pressed_right && !neighbours[1].expired()) {
            is_key_pressed = true;
            r_selected = 1;
        } else if (pressed_down && !neighbours[2].expired()) {
            is_key_pressed = true;
            r_selected = 2;
        } else if (pressed_left && !neighbours[3].expired()) {
            is_key_pressed = true;
            r_selected = 3;
        } else if (pressed_enter) {
            is_key_pressed = true;
            gm->changeState(GUIGameState::kEvent);
        }
        render(r, d);
    }

    void render(std::shared_ptr<graphics::Renderer> r, std::shared_ptr<dungeon::Dungeon> d) {
        r->clear();
        std::vector<std::shared_ptr<dungeon::Cell>> cells = d->getCells();
        auto current = d->getCurrentCell().lock();
        float cx = static_cast<float>(current->getPosition().first) * cfg::CELL_SIZE;
        float cy = static_cast<float>(current->getPosition().second) * cfg::CELL_SIZE;
        float x_offset = cx - cfg::WINDOW_WIDTH * 3 / 4;
        float y_offset = cy - cfg::WINDOW_HEIGHT / 2;
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
            if (cell == d->getCurrentCell().lock()) {
                m_current_cell_sprite->toSize(w, w);
                r->draw(*m_current_cell_sprite, x, y);
            }
            if (cell == neighbours[r_selected].lock()) {
                m_selected_room_sprite->toSize(w, w);
                r->draw(*m_selected_room_sprite, x, y);
            }
        }
        r->display();
    }

    void exit(GameMachine *gm) {
        // gm->m_engine.lock().get()->getDungeon()->setTargetRoom(neighbours[r_selected]);
        gm->m_engine.lock()->getDungeon()->setCurrentCell(neighbours[r_selected].lock());
    }

private:
    bool is_key_pressed = false;
    int r_selected = 0;
    std::vector<std::weak_ptr<dungeon::Room>> neighbours;

    std::map<dungeon::CellType, std::shared_ptr<graphics::Sprite>> m_room_sprites;
    std::map<dungeon::CellType, std::shared_ptr<graphics::Sprite>> m_hall_sprites;

    std::shared_ptr<graphics::Sprite> m_selected_room_sprite;
    std::shared_ptr<graphics::Sprite> m_current_cell_sprite;

    std::shared_ptr<graphics::Sprite> m_visited_room_sprite;
    std::shared_ptr<graphics::Sprite> m_not_visited_room_sprite;
    std::shared_ptr<graphics::Sprite> m_not_visited_hall_sprite;
};
}   // namespace game
}   // namespace gui