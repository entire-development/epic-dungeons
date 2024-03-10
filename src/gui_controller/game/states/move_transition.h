#pragma once
#include "dungeon/dungeon.h"
#include "gui_controller/game/game_machine.h"
#include "gui_controller/keyboard_manager/keyboard_manager.h"
#include "gui_controller/timed_count.h"
#include "gui_controller/utils.h"
#include "static_data/game_config.h"
#include <cmath>
#include <map>
#include <memory>

namespace gui {
namespace game {
class MoveTransition : public GameState {
public:
    MoveTransition() {
        m_gradient = std::make_shared<graphics::Sprite>("utils/gradient.png");
        m_gradient->setRotation(-90);
        m_gradient->toSize(cfg::WINDOW_HEIGHT, cfg::WINDOW_WIDTH * 1.5);

        auto sigm = [](float x) {
            return 1 / (1 + std::exp(-10 * (x - 0.5)));
        };
        m_anim.init(0, 1, 500, sigm);
    }

    virtual void enter(GameMachine *gm) {
        m_anim.start();
    }

    virtual void update(GameMachine *gm) {
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        std::shared_ptr<dungeon::Dungeon> d = gm->m_engine.lock().get()->getDungeon();
        m_anim.update(gm->getDeltaTime());
        if (m_anim.isEnded()) {
            gm->changeState(GUIGameState::kEvent);
        }
        render(r, d);
    }

    void render(std::shared_ptr<graphics::Renderer> r, std::shared_ptr<dungeon::Dungeon> d) {
        std::shared_ptr<dungeon::Cell> current = d->getCurrentCell().lock();
        std::shared_ptr<dungeon::Cell> next_cell = d->getNextCell().lock();
        float animation_progress = m_anim.get();
        r->clear();
        utils::cellView(r, d, animation_progress);
        r->draw(*m_gradient, -(cfg::WINDOW_WIDTH / 2), cfg::WINDOW_HEIGHT);
        Vector2d center = {cfg::WINDOW_WIDTH * 4 / 5, cfg::WINDOW_HEIGHT / 2};
        utils::drawMap(r, d, center, cfg::CELL_SIZE, animation_progress);
        r->display();
    }

    void exit(GameMachine *gm) {
        gm->m_engine.lock()->getDungeon()->setCurrentCell(gm->m_engine.lock()->getDungeon()->getNextCell().lock());
    }

private:
    TimedCount m_anim;
    std::shared_ptr<graphics::Sprite> m_gradient;
};
}   // namespace game
}   // namespace gui