#pragma once
#include "gui_controller/game/game_machine.h"
#include "static_data/game_config.h"
#include "dungeon/dungeon.h"
#include "keyboard/keyboard.h"

namespace gui {
namespace game {
class RoomSelection : public GameState {

    virtual void enter(GameMachine *gm) {
        std::shared_ptr<dungeon::Dungeon> d = gm->m_engine.lock().get()->getDungeon();
        neighbours = d->getRoomNeighbours(dynamic_cast<dungeon::Room *>(d->getCurrentCell()));
        renderer::SFMLRenderer *r = gm->m_renderer.lock().get();
        render(r, d);

    }

    void selection(renderer::SFMLRenderer *r, std::shared_ptr<dungeon::Dungeon> d) {
        bool pressed_up = keyboard::isPressed(keyboard::KEY_UP) || keyboard::isPressed(keyboard::KEY_W);
        bool pressed_down = keyboard::isPressed(keyboard::KEY_DOWN) || keyboard::isPressed(keyboard::KEY_S);
        bool pressed_enter = keyboard::isPressed(keyboard::KEY_ENTER);
        
        if (pressed_up) {
            r_selected = (r_selected + 1) % neighbours.size();
        } else if (pressed_down) {
            r_selected = (r_selected - 1 + neighbours.size()) % neighbours.size();
        }
    }
    
    void render(renderer::SFMLRenderer *r, std::shared_ptr<dungeon::Dungeon> d) {
        r->clear();
        r->drawText(50, 50, "Select a room");
        std::vector<dungeon::Cell *> cells = d->getCells();
        for (auto cell : cells) {
            float x = static_cast<float>(cell->getPosition().first);
            float y = static_cast<float>(cell->getPosition().second);
            if (cell->isRoom()) {
                r->drawRec({x * cfg::CELL_SIZE - 1, y * cfg::CELL_SIZE - 1, 3 * cfg::CELL_SIZE, 3 * cfg::CELL_SIZE, sf::Color::Red});
            } else {
                r->drawRec({x * cfg::CELL_SIZE - 1, y * cfg::CELL_SIZE - 1, cfg::CELL_SIZE, cfg::CELL_SIZE, sf::Color::Blue});
            }
        }
        r->display();
    }

    void exit(GameMachine *gm) {
        gm->m_engine.lock().get()->getDungeon()->setTargetRoom(neighbours[r_selected]);
    }

private:
    int r_selected = 0;
    std::vector<dungeon::Room *> neighbours;
    

};
}   // namespace game
}   // namespace gui