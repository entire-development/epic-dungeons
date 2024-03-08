#pragma once
#include "dungeon/dungeon.h"
#include "gui_controller/game/game_machine.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <memory>

namespace gui {
namespace game {
class RoomSelection : public GameState {
    virtual void enter(GameMachine *gm) {
        std::shared_ptr<dungeon::Dungeon> d = gm->m_engine.lock().get()->getDungeon();
        neighbours = d->getRoomNeighbours(std::dynamic_pointer_cast<dungeon::Room>(d->getCurrentCell().lock()));
        graphics::Renderer *r = gm->m_renderer.lock().get();
        render(r, d);
    }

    virtual void update(GameMachine *gm) {
        graphics::Renderer *r = gm->m_renderer.lock().get();
        std::shared_ptr<dungeon::Dungeon> d = gm->m_engine.lock().get()->getDungeon();
        bool pressed_right = keyboard::isPressed(keyboard::KEY_RIGHT) || keyboard::isPressed(keyboard::KEY_D);
        bool pressed_left = keyboard::isPressed(keyboard::KEY_LEFT) || keyboard::isPressed(keyboard::KEY_LEFT);
        bool pressed_enter = keyboard::isPressed(keyboard::KEY_ENTER);

        if (!(pressed_right || pressed_left))
            is_key_pressed = false;

        if (is_key_pressed)
            return;

        if (pressed_right) {
            r_selected = (r_selected + 1) % neighbours.size();
            is_key_pressed = true;
            render(r, d, neighbours[r_selected].lock());
        } else if (pressed_left) {
            r_selected = (r_selected - 1 + neighbours.size()) % neighbours.size();
            is_key_pressed = true;
            render(r, d, neighbours[r_selected].lock());
        } else if (pressed_enter) {
            // next state
        }
    }

    void render(graphics::Renderer *r, std::shared_ptr<dungeon::Dungeon> d, std::shared_ptr<dungeon::Cell> selected_room = nullptr) {
        r->clear();
        r->drawText(50, 50, "Select a room");
        std::vector<std::shared_ptr<dungeon::Cell>> cells = d->getCells();
        for (auto cell : cells) {
            float x = static_cast<float>(cell->getPosition().first);
            float y = static_cast<float>(cell->getPosition().second);
            if (cell->isRoom()) {
                if (cell == d->getCurrentCell().lock()) {
                    r->drawRec({(x - 1) * CELL_SIZE, (y - 1) * CELL_SIZE, ROOM_SIZE, ROOM_SIZE, ROOM_COLOR, -1, CURRENT_ROOM_STROKE_COLOR});
                } else if (cell == selected_room) {
                    r->drawRec({(x - 1) * CELL_SIZE, (y - 1) * CELL_SIZE, ROOM_SIZE, ROOM_SIZE,
                            ROOM_COLOR, -1, SELECTED_ROOM_STROKE_COLOR});
                } else {
                    r->drawRec({(x - 1) * CELL_SIZE, (y - 1) * CELL_SIZE, ROOM_SIZE, ROOM_SIZE,
                            ROOM_COLOR, -1});
                }
            } else {
                r->drawRec(
                    {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_COLOR, -1});
            }
        }
        r->display();
    }

    void exit(GameMachine *gm) {
        gm->m_engine.lock().get()->getDungeon()->setTargetRoom(neighbours[r_selected]);
    }

private:
    const float CELL_SIZE = cfg::CELL_SIZE;
    const float ROOM_SIZE = 3 * cfg::CELL_SIZE;

    const std::string ROOM_COLOR = "#cc2e0e";
    const std::string CELL_COLOR = "#edaf1c";
    const std::string CURRENT_ROOM_STROKE_COLOR = "#140ecc";
    const std::string SELECTED_ROOM_STROKE_COLOR = "#ffffff";

    bool is_key_pressed = false;
    int r_selected = 0;
    std::vector<std::weak_ptr<dungeon::Room>> neighbours;
};
}   // namespace game
}   // namespace gui