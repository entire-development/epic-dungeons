#pragma once
#include "dungeon/dungeon.h"
#include "gui_controller/game/game_machine.h"
#include "gui_controller/utils.h"
#include "keyboard/keyboard.h"
#include "static_data/game_config.h"
#include <cmath>
#include <map>
#include <memory>

namespace gui {
namespace game {
class RoomSelection : public GameState {
public:
    RoomSelection() {
        m_hall_background = std::make_shared<graphics::Sprite>("background/hall/crypts/empty.png");
        m_hall_background->toSizeY(cfg::WINDOW_HEIGHT * 5 / 6);
        m_hall_background_width = m_hall_background->getSize().x();
        m_room_background = std::make_shared<graphics::Sprite>("background/room/crypts/empty.png");
        m_room_background->toSizeY(cfg::WINDOW_HEIGHT * 5 / 6);

        m_gradient = std::make_shared<graphics::Sprite>("utils/gradient.png");
        m_gradient->setRotation(-90);
        m_gradient->toSize(cfg::WINDOW_HEIGHT, cfg::WINDOW_WIDTH * 1.5);
    }

    virtual void enter(GameMachine *gm) {
        is_key_pressed = true;
        std::shared_ptr<dungeon::Dungeon> d = gm->m_engine.lock().get()->getDungeon();
        std::shared_ptr<dungeon::Cell> current = d->getCurrentCell().lock();
        is_in_room = current->isRoom();
        if (is_in_room) {
            m_background = m_room_background;
            neighbours = d->getRoomNeighbours(std::dynamic_pointer_cast<dungeon::Room>(current));
            while (neighbours[r_selected].expired()) {
                r_selected = (r_selected + 1) % 4;
            }
            d->setTargetRoom(neighbours[r_selected].lock());
        } else {
            distance_to_target = d->getDistanceToTarget();
            m_background = m_hall_background;
        }
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        render(r, d);
    }

    virtual void update(GameMachine *gm) {
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        std::shared_ptr<dungeon::Dungeon> d = gm->m_engine.lock().get()->getDungeon();

        if (animation) {
            m_timer += gm->getDeltaTime();
            if (m_timer >= m_duration) {
                animation = false;
                gm->changeState(GUIGameState::kEvent);
            }
            float progress = (float) m_timer / m_duration;
            progress = 1 / (1 + std::exp(-10 * (progress - 0.5)));
            render(r, d, progress);
            return;
        }

        bool pressed_up = keyboard::isPressed(keyboard::KEY_UP) || keyboard::isPressed(keyboard::KEY_W);
        bool pressed_down = keyboard::isPressed(keyboard::KEY_DOWN) || keyboard::isPressed(keyboard::KEY_S);
        bool pressed_right = keyboard::isPressed(keyboard::KEY_RIGHT) || keyboard::isPressed(keyboard::KEY_D);
        bool pressed_left = keyboard::isPressed(keyboard::KEY_LEFT) || keyboard::isPressed(keyboard::KEY_A);
        bool pressed_enter = keyboard::isPressed(keyboard::KEY_ENTER) || keyboard::isPressed(keyboard::KEY_SPACE);

        if (!is_in_room) {
            if (pressed_right) {
                is_key_pressed = true;
                d->setNextCell(d->getNextOnPath().lock());
                m_timer = 0;
                animation = true;
                m_direction = 1;
            } else if (pressed_left) {
                is_key_pressed = true;
                d->setNextCell(d->getPrevOnPath().lock());
                m_timer = 0;
                animation = true;
                m_direction = -1;
            }
            return;
        }

        if (!(pressed_right || pressed_left || pressed_enter || pressed_up || pressed_down))
            is_key_pressed = false;
        if (is_key_pressed)
            return;

        if (pressed_up && !neighbours[0].expired()) {
            is_key_pressed = true;
            r_selected = 0;
            d->setTargetRoom(neighbours[r_selected].lock());
        } else if (pressed_right && !neighbours[1].expired()) {
            is_key_pressed = true;
            r_selected = 1;
            d->setTargetRoom(neighbours[r_selected].lock());
        } else if (pressed_down && !neighbours[2].expired()) {
            is_key_pressed = true;
            r_selected = 2;
            d->setTargetRoom(neighbours[r_selected].lock());
        } else if (pressed_left && !neighbours[3].expired()) {
            is_key_pressed = true;
            r_selected = 3;
            d->setTargetRoom(neighbours[r_selected].lock());
        } else if (pressed_enter) {
            is_key_pressed = true;
            d->setNextCell(d->getNextOnPath().lock());
            hall_length = gm->m_engine.lock()->getDungeon()->getDistanceToTarget() - 1;
            m_timer = 0;
            animation = true;
            m_direction = 1;
            // gm->changeState(GUIGameState::kEvent);
        }

        if (is_key_pressed)
            render(r, d);
    }

    void render(std::shared_ptr<graphics::Renderer> r, std::shared_ptr<dungeon::Dungeon> d,
                float animation_progress = 0.0f) {
        r->clear();
        float background_x = 0;
        if (!is_in_room) {
            background_x = ((float) ((hall_length - distance_to_target) % 4) + animation_progress * m_direction) / 4;
            background_x = m_hall_background_width * background_x;
        }
        r->draw(*m_background, -background_x, 0);
        r->draw(*m_background, m_hall_background_width - background_x - 5, 0);
        r->draw(*m_background, -m_hall_background_width - background_x + 5, 0);

        r->draw(*m_gradient, -(cfg::WINDOW_WIDTH / 2), cfg::WINDOW_HEIGHT);
        utils::drawMap(r, d, Vector2d(cfg::WINDOW_WIDTH * 4 / 5, cfg::WINDOW_HEIGHT / 2), animation_progress);
        r->display();
    }

    void exit(GameMachine *gm) {
        gm->m_engine.lock()->getDungeon()->setCurrentCell(gm->m_engine.lock()->getDungeon()->getNextCell().lock());
    }

private:
    uint64_t m_timer = 0;
    uint64_t m_duration = 500;
    bool animation = false;
    int m_direction = 1;

    bool is_in_room = true;
    bool is_key_pressed = false;
    int r_selected = 0;
    uint32_t hall_length = 0;
    uint32_t distance_to_target = 0;
    std::vector<std::weak_ptr<dungeon::Room>> neighbours;

    std::shared_ptr<graphics::Sprite> m_background;
    std::shared_ptr<graphics::Sprite> m_hall_background;
    std::shared_ptr<graphics::Sprite> m_room_background;
    float m_hall_background_width;
    std::shared_ptr<graphics::Sprite> m_gradient;
    std::vector<std::shared_ptr<graphics::Sprite>> m_room_sprites;
    std::vector<std::shared_ptr<graphics::Sprite>> m_hall_sprites;
};
}   // namespace game
}   // namespace gui