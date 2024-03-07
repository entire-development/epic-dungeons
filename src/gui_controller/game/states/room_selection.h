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
        // selection(gm->m_renderer.lock().get(), gm->m_engine.lock().get()->getDungeon());
        // render(gm->m_renderer.lock().get(), gm->m_engine.lock().get()->getDungeon());
    }

    void selection(graphics::Renderer *r, std::shared_ptr<dungeon::Dungeon> d) {
        bool pressed_up = keyboard::isPressed(keyboard::KEY_UP) || keyboard::isPressed(keyboard::KEY_W);
        bool pressed_down = keyboard::isPressed(keyboard::KEY_DOWN) || keyboard::isPressed(keyboard::KEY_S);
        bool pressed_enter = keyboard::isPressed(keyboard::KEY_ENTER);

        if (pressed_up) {
            r_selected = (r_selected + 1) % neighbours.size();
        } else if (pressed_down) {
            r_selected = (r_selected - 1 + neighbours.size()) % neighbours.size();
        }
    }

    void render(graphics::Renderer *r, std::shared_ptr<dungeon::Dungeon> d) {
        r->clear();
        r->drawText(50, 50, "Select a room");
        std::vector<std::shared_ptr<dungeon::Cell>> cells = d->getCells();
        for (auto cell : cells) {
            float x = static_cast<float>(cell->getPosition().first);
            float y = static_cast<float>(cell->getPosition().second);
            if (cell->isRoom()) {
                r->drawRec({(x - 1) * cfg::CELL_SIZE, (y - 1) * cfg::CELL_SIZE, 3 * cfg::CELL_SIZE, 3 * cfg::CELL_SIZE,
                            sf::Color::Red, -1});
            } else {
                r->drawRec(
                    {x * cfg::CELL_SIZE, y * cfg::CELL_SIZE, cfg::CELL_SIZE, cfg::CELL_SIZE, sf::Color::Blue, -1});
            }
        }
        r->display();
    }

    void exit(GameMachine *gm) {
        gm->m_engine.lock().get()->getDungeon()->setTargetRoom(neighbours[r_selected]);
    }

private:
    int r_selected = 0;
    std::vector<std::weak_ptr<dungeon::Room>> neighbours;
};
}   // namespace game
}   // namespace gui