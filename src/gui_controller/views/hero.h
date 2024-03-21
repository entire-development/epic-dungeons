#pragma once
#include "engine/entity.h"
#include "renderer/graphics.h"
#include "vector2d/vector2d.h"
#include <memory>
#include <string>

namespace gui {
namespace views {

class Entity {
public:
    Entity(const std::shared_ptr<engine::entities::Entity> &entity) {
        bind(entity);
        reset();
    }

    enum class State {
        kIdle,
        kCombat,
    };

    enum class Selection {
        kNone,
        kSelected,
        kTarget,
        kSelectable,
        kTargetable,
        kNotSelectable,
        kNotTargetable,
    };

    void setState(const State &state) {
        m_state = state;
    }

    void setSelection(const Selection &selection) {
        m_selection = selection;
    }

    const std::weak_ptr<engine::entities::Entity> &getEntity() const {
        return m_entity;
    }

    const void render(const std::shared_ptr<graphics::Renderer> &renderer, const uint8_t &position,
                      const float &animation_progress = 0);

    std::shared_ptr<graphics::Sprite> getPortrait() {
        return m_portrait;
    }

    void reset() {
        m_state = State::kIdle;
        m_selection = Selection::kNone;
    }

    void bind(const std::shared_ptr<engine::entities::Entity> &entity);

    bool isMine(const std::shared_ptr<engine::entities::Entity> &entity) {
        return m_entity.lock() == entity;
    }

protected:
    std::weak_ptr<engine::entities::Entity> m_entity;
    std::map<State, std::shared_ptr<graphics::Animation>> m_animations;
    std::shared_ptr<graphics::Sprite> m_portrait;
    State m_state;
    Selection m_selection;
};

}   // namespace views
}   // namespace gui