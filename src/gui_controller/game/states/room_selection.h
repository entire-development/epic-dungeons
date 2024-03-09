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
        is_key_pressed = true;
        r_selected = 0;
        std::shared_ptr<dungeon::Dungeon> d = gm->m_engine.lock().get()->getDungeon();
        neighbours = d->getRoomNeighbours(std::dynamic_pointer_cast<dungeon::Room>(d->getCurrentCell().lock()));
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        render(r, d);
    }

    virtual void update(GameMachine *gm) {
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        std::shared_ptr<dungeon::Dungeon> d = gm->m_engine.lock().get()->getDungeon();
        bool pressed_right = keyboard::isPressed(keyboard::KEY_RIGHT) || keyboard::isPressed(keyboard::KEY_D);
        bool pressed_left = keyboard::isPressed(keyboard::KEY_LEFT) || keyboard::isPressed(keyboard::KEY_A);
        bool pressed_enter = keyboard::isPressed(keyboard::KEY_ENTER);

        if (!(pressed_right || pressed_left || pressed_enter))
            is_key_pressed = false;

        if (is_key_pressed)
            return;

        if (pressed_right) {
            r_selected = (r_selected + 1) % neighbours.size();
            is_key_pressed = true;
            render(r, d);
        } else if (pressed_left) {
            r_selected = (r_selected - 1 + neighbours.size()) % neighbours.size();
            is_key_pressed = true;
            render(r, d);
        } else if (pressed_enter) {
            // next state
            gm->changeState(GUIGameState::kEvent);
        }
    }

    void render(std::shared_ptr<graphics::Renderer> r, std::shared_ptr<dungeon::Dungeon> d) {
        r->clear();
        r->drawText(50, 50, "Select a room");
        std::vector<std::shared_ptr<dungeon::Cell>> cells = d->getCells();
        for (auto cell : cells) {
            float x = static_cast<float>(cell->getPosition().first) * cfg::CELL_SIZE;
            float y = static_cast<float>(cell->getPosition().second) * cfg::CELL_SIZE;
            float w = cfg::CELL_SIZE;
            graphics::Color color = "#edaf1c";
            graphics::Color stroke_color = "#000000";
            if (cell->isRoom()) {
                x -= cfg::CELL_SIZE;
                y -= cfg::CELL_SIZE;
                w = cfg::CELL_SIZE * 3;
                printf("cell type: %d\n", cell->getType());
                if (cell->getType() == dungeon::CellType::FIGHT)
                    color = "#cc2e0e";
                if (cell->getType() == dungeon::CellType::SHOP)
                    color = "#0ecc14";
                if (!cell->isVisited())
                    color = "#8c8c8c";
            }
            if (cell == neighbours[r_selected].lock())
                stroke_color = "#ffffff";
            if (cell == d->getCurrentCell().lock())
                stroke_color = "#140ecc";
            r->drawRec({x, y, w, w, color, -1, stroke_color});
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
};
}   // namespace game
}   // namespace gui