#pragma once
#include "dungeon/dungeon.h"
#include "engine/entities.h"
#include "gui_controller/game/game_machine.h"
#include "gui_controller/keyboard_manager/keyboard_manager.h"
#include "gui_controller/utils.h"
#include "gui_controller/views/hero.h"
#include "keyboard/keyboard.h"
#include "logging/logger.h"
#include "static_data/game_config.h"
#include <cmath>
#include <memory>

namespace gui {
namespace game {
class Battle : public GameState {
public:
    enum class BattleState {
        kNone,
        kEnemyAttack,
        kSkillSelection,
        kDefenderSelection,
        kAttack,
    };

    Battle() : GameState() {}

    virtual void freeze(GameMachine *gm) {}

    virtual void unfreeze(GameMachine *gm) {}

    virtual void enter(GameMachine *gm) {
        m_keyboard.reset();
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        m_enemy_party = std::make_shared<engine::entities::Party>();
        m_enemy_party->addMember(std::make_shared<engine::entities::Abomination>());
        m_enemy_party->addMember(std::make_shared<engine::entities::Antiquarian>());
        m_enemy_party->addMember(std::make_shared<engine::entities::Arbalest>());
        auto party = gm->m_engine.lock()->getParty();

        // bad code
        /// @todo create better way to bind entities and views
        /// now there is data replication between engine and views, which is bad and may lead to bugs
        m_heroes.clear();
        for (size_t i = 0; i < party->getMembersCount(); i++)
            m_heroes.push_back(std::make_shared<views::Entity>(party->getMember(i)));

        m_enemies.clear();
        for (size_t i = 0; i < m_enemy_party->getMembersCount(); i++)
            m_enemies.push_back(std::make_shared<views::Entity>(m_enemy_party->getMember(i)));
        // end of bad code

        m_selected = 0;
        m_current = 0;
        m_selected_skill = 0;
        m_selected_defender = 0;
        m_attacker.reset();
        m_defenders.clear();
        m_skill.reset();
        m_state = BattleState::kNone;

        m_queue.clear();
        for (auto &hero : m_heroes) {
            hero->setState(views::Entity::State::kCombat);
            m_queue.push_back(hero);
        }
        for (auto &enemy : m_enemies) {
            enemy->setState(views::Entity::State::kCombat);
            m_queue.push_back(enemy);
        }

        // sort by speed(descending)
        std::sort(m_queue.begin(), m_queue.end(),
                  [](const std::weak_ptr<views::Entity> &a, const std::weak_ptr<views::Entity> &b) {
                      return a.lock()->getEntity().lock()->getSpeed() > b.lock()->getEntity().lock()->getSpeed();
                  });
        logging::debug("First in queue: " + std::to_string(m_queue[0].lock()->getEntity().lock()->getSpeed()));
        logging::debug("Last in queue: "
                       + std::to_string(m_queue[m_queue.size() - 1].lock()->getEntity().lock()->getSpeed()));

        render(gm);
    }

    const std::shared_ptr<views::Entity> getEntityView(const std::shared_ptr<engine::entities::Entity> &entity) {
        for (auto &hero : m_heroes)
            if (hero->isMine(entity))
                return hero;
        for (auto &enemy : m_enemies)
            if (enemy->isMine(entity))
                return enemy;
        return nullptr;
    }

    void skill_selection(GameMachine *gm) {
        std::shared_ptr<views::Entity> attacker = m_queue[m_current].lock();
        std::vector<std::shared_ptr<engine::skills::Skill>> skills = attacker->getEntity().lock()->getSkills();
        if (m_keyboard.isClicked(keyboard::KEY_ENTER) || m_keyboard.isClicked(keyboard::KEY_SPACE)
            || m_keyboard.isClicked(keyboard::KEY_W) || m_keyboard.isClicked(keyboard::KEY_UP)) {
            m_skill = std::dynamic_pointer_cast<engine::skills::CombatSkill>(skills[m_selected_skill]);
            m_state = BattleState::kDefenderSelection;
            logging::debug("Skill selected: " + m_skill.lock()->name);

            for (auto &enemy : m_enemies) {
                if (!enemy->getEntity().lock()->isAlive())
                    enemy->setSelection(views::Entity::Selection::kNotTargetable);
            }
            for (auto &hero : m_heroes) {
                if (!hero->getEntity().lock()->isAlive())
                    hero->setSelection(views::Entity::Selection::kNotSelectable);
            }

            if (m_skill.lock()->targetType == engine::skills::TargetType::kIndividual) {
                for (auto &enemy : m_enemies) {
                    if (enemy->getEntity().lock()->isAlive())
                        enemy->setSelection(views::Entity::Selection::kTargetable);
                }
                getEntityView(m_enemy_party->getMember(0))->setSelection(views::Entity::Selection::kTarget);
            }
            if (m_skill.lock()->targetType == engine::skills::TargetType::kParty) {
                for (auto &hero : m_heroes) {
                    if (hero->getEntity().lock()->isAlive())
                        hero->setSelection(views::Entity::Selection::kSelected);
                }
            }
            if (m_skill.lock()->targetType == engine::skills::TargetType::kOtherParty) {
                for (auto &enemy : m_enemies) {
                    if (enemy->getEntity().lock()->isAlive())
                        enemy->setSelection(views::Entity::Selection::kTargetable);
                }
            }
        }
        if (m_keyboard.isClicked(keyboard::KEY_RIGHT) || m_keyboard.isClicked(keyboard::KEY_D)) {
            m_selected_skill = (m_selected_skill + 1) % skills.size();
        }
        if (m_keyboard.isClicked(keyboard::KEY_LEFT) || m_keyboard.isClicked(keyboard::KEY_A)) {
            m_selected_skill = (m_selected_skill - 1 + skills.size()) % skills.size();
        }
    }

    void enemy_attack(GameMachine *gm) {
        m_attacker = m_queue[m_current];
        std::shared_ptr<engine::entities::Entity> entity = m_attacker.lock()->getEntity().lock();
        m_skill = std::dynamic_pointer_cast<engine::skills::CombatSkill>(
            entity->getSkills()[rand() % entity->getSkills().size()]);
        std::shared_ptr<engine::entities::Party> target_party = gm->m_engine.lock()->getParty();

        m_defenders.clear();
        if (m_skill.lock()->targetType == engine::skills::TargetType::kIndividual) {
            m_defenders.push_back(
                getEntityView(target_party->getMember(rand() % target_party->getAliveMembersCount())));
        } else if (m_skill.lock()->targetType == engine::skills::TargetType::kOtherParty) {
            m_defenders.clear();
            for (size_t i = 0; i < m_heroes.size(); i++)
                if (m_heroes[i]->getEntity().lock()->isAlive())
                    m_defenders.push_back(m_heroes[i]);
        } else if (m_skill.lock()->targetType == engine::skills::TargetType::kParty) {
            m_defenders.clear();
            for (size_t i = 0; i < m_enemies.size(); i++)
                if (m_enemies[i]->getEntity().lock()->isAlive())
                    m_defenders.push_back(m_enemies[i]);
        }
        logging::debug("Enemy attacks with " + m_skill.lock()->name);
        m_state = BattleState::kAttack;
    }

    void attack(GameMachine *gm) {
        std::shared_ptr<views::Entity> attacker = m_queue[m_current].lock();
        std::shared_ptr<engine::entities::Entity> entity = attacker->getEntity().lock();
        std::shared_ptr<engine::entities::Party> target_party = gm->m_engine.lock()->getParty();

        for (auto &defender : m_defenders) {
            std::shared_ptr<engine::entities::Entity> target = defender.lock()->getEntity().lock();
            engine::skills::AttackResult result = target->takeAttack(entity, m_skill.lock());
            if (result.isHit) {
                logging::debug("Hit! Damage: " + std::to_string(result.damage));
                if (result.isCritical)
                    logging::debug("Critical hit!");
                if (result.damage > 0) {
                    logging::debug("Target health: " + std::to_string(target->getHealth()));
                }
            } else {
                logging::debug("Miss!");
            }
        }
        m_current = (m_current + 1) % m_queue.size();
        m_state = BattleState::kNone;
    }

    void defender_selection(GameMachine *gm) {
        if (m_keyboard.isClicked(keyboard::KEY_ENTER)) {
            for (auto &enemy : m_enemies) {
                enemy->setSelection(views::Entity::Selection::kNone);
            }
            for (auto &hero : m_heroes) {
                hero->setSelection(views::Entity::Selection::kNone);
            }

            if (m_skill.lock()->targetType == engine::skills::TargetType::kIndividual) {
                m_defenders.clear();
                std::shared_ptr<engine::entities::Entity> target = m_enemy_party->getMember(m_selected_defender);
                m_defenders.push_back(getEntityView(target));
            }
            if (m_skill.lock()->targetType == engine::skills::TargetType::kParty) {
                m_defenders.clear();
                for (size_t i = 0; i < m_heroes.size(); i++)
                    if (m_heroes[i]->getEntity().lock()->isAlive())
                        m_defenders.push_back(m_heroes[i]);
            }
            if (m_skill.lock()->targetType == engine::skills::TargetType::kOtherParty) {
                m_defenders.clear();
                for (size_t i = 0; i < m_enemies.size(); i++)
                    if (m_enemies[i]->getEntity().lock()->isAlive())
                        m_defenders.push_back(m_enemies[i]);
            }

            m_state = BattleState::kAttack;
            return;
        }
        if (m_keyboard.isClicked(keyboard::KEY_DOWN) || m_keyboard.isClicked(keyboard::KEY_S)) {
            for (auto &enemy : m_enemies) {
                enemy->setSelection(views::Entity::Selection::kNone);
            }
            for (auto &hero : m_heroes) {
                hero->setSelection(views::Entity::Selection::kNone);
            }
            m_state = BattleState::kSkillSelection;
            return;
        }

        if (m_skill.lock()->targetType == engine::skills::TargetType::kIndividual) {
            const uint8_t defenders_count = m_enemy_party->getAliveMembersCount();
            getEntityView(m_enemy_party->getMember(m_selected_defender))
                ->setSelection(views::Entity::Selection::kTargetable);
            if (m_keyboard.isClicked(keyboard::KEY_RIGHT) || m_keyboard.isClicked(keyboard::KEY_D)) {
                m_selected_defender = (m_selected_defender + 1) % defenders_count;
            }
            if (m_keyboard.isClicked(keyboard::KEY_LEFT) || m_keyboard.isClicked(keyboard::KEY_A)) {
                m_selected_defender = (m_selected_defender - 1 + defenders_count) % defenders_count;
            }
            getEntityView(m_enemy_party->getMember(m_selected_defender))
                ->setSelection(views::Entity::Selection::kTarget);
        }

        render(gm);
    }

    void routing(GameMachine *gm) {
        if (!m_queue[m_current].lock()->getEntity().lock()->isAlive()) {
            m_current = (m_current + 1) % m_queue.size();
        }
        bool all_dead = true;
        for (auto &hero : m_heroes) {
            if (hero->getEntity().lock()->isAlive()) {
                all_dead = false;
                break;
            }
        }
        if (all_dead) {
            gm->changeState(GUIGameState::kGameOver);
        }
        all_dead = true;
        for (auto &enemy : m_enemies) {
            if (enemy->getEntity().lock()->isAlive()) {
                all_dead = false;
                break;
            }
        }
        if (all_dead) {
            gm->changeState(GUIGameState::kPostEvent);
        }

        if (m_queue[m_current].lock()->getEntity().lock()->getParty() == gm->m_engine.lock()->getParty()) {
            m_state = BattleState::kSkillSelection;
            logging::debug("Player's turn");
        } else {
            m_state = BattleState::kEnemyAttack;
            logging::debug("Enemy's turn");
        }
    }

    virtual void update(GameMachine *gm) {
        m_keyboard.update();

        switch (m_state) {
            case BattleState::kNone:
                routing(gm);
                break;
            case BattleState::kEnemyAttack:
                enemy_attack(gm);
                break;
            case BattleState::kAttack:
                attack(gm);
                break;
            case BattleState::kSkillSelection:
                skill_selection(gm);
                break;
            case BattleState::kDefenderSelection:
                defender_selection(gm);
                break;
            default:
                break;
        }
        render(gm);
    }

    void render(GameMachine *gm) {
        std::shared_ptr<graphics::Renderer> r = gm->m_renderer.lock();
        std::shared_ptr<dungeon::Cell> cell = gm->m_engine.lock()->getDungeon()->getCurrentCell().lock();
        std::shared_ptr<dungeon::Dungeon> dungeon = gm->m_engine.lock()->getDungeon();
        std::shared_ptr<engine::entities::Party> party = gm->m_engine.lock()->getParty();
        r->clear();
        utils::cellView(r, dungeon);

        for (size_t i = 0; i < party->getMembersCount(); i++)
            getEntityView(party->getMember(i))->render(r, 3 - i);
        for (size_t i = 0; i < m_enemy_party->getMembersCount(); i++)
            getEntityView(m_enemy_party->getMember(i))->render(r, i + 4);

        utils::drawQueue(r, m_queue, m_current);

        if (m_state == BattleState::kSkillSelection) {
            std::shared_ptr<views::Entity> attacker = m_queue[m_current].lock();
            std::vector<std::shared_ptr<engine::skills::Skill>> skills = attacker->getEntity().lock()->getSkills();
            utils::drawSkills(r, skills, m_selected_skill);
        }
        r->display();
    }

private:
    std::shared_ptr<engine::entities::Party> m_enemy_party;
    KeyboardManager m_keyboard;
    uint8_t m_selected = 0;
    uint8_t m_selected_skill = 0;
    uint8_t m_selected_defender = 0;
    uint8_t m_current = 0;

    std::weak_ptr<views::Entity> m_attacker;
    std::vector<std::weak_ptr<views::Entity>> m_defenders;
    std::weak_ptr<engine::skills::CombatSkill> m_skill;

    std::vector<std::weak_ptr<views::Entity>> m_queue;

    std::vector<std::shared_ptr<views::Entity>> m_heroes;
    std::vector<std::shared_ptr<views::Entity>> m_enemies;

    BattleState m_state = BattleState::kNone;
};

}   // namespace game
}   // namespace gui