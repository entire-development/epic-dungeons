#pragma once
#include "engine/engine.h"
#include "renderer/graphics.h"

namespace gui {
class Controller;
class State;
enum class GUIState {
    kMainMenu,
    kSettings,
    kGame,
    kFight,
    kRoomSelection,
    kDirectionChoice,
    kGameOver,
    kExit,
};

class State {
    friend class Controller;

public:
    virtual void enter(Controller *controller) {}

    virtual void update(Controller *controller) {}

    virtual void exit(Controller *controller) {}
};

class Controller {
    friend class State;

public:
    Controller(graphics::Renderer &renderer, engine::Engine &engine);

    template<typename T>
    void addState(const GUIState &state) {
        m_states[state] = std::make_shared<T>();
    }

    void changeState(const GUIState &state) {
        m_next_state = m_states[state];
    }

    void update() {
        if (m_next_state) {
            m_current_state = m_next_state;
            m_next_state = nullptr;
            m_current_state->enter(this);
        }
        if (m_current_state) {
            m_current_state->update(this);
        }
        if (m_next_state) {
            if (m_current_state) {
                m_current_state->exit(this);
            }
        }
    }

    uint64_t getDeltaTime() {
        return delta_time;
    }

    void setDeltaTime(uint64_t dt) {
        delta_time = dt;
    }

    graphics::Renderer &m_renderer;
    engine::Engine &m_engine;

protected:
    uint64_t delta_time;
    std::shared_ptr<State> m_current_state;
    std::shared_ptr<State> m_next_state;
    std::map<GUIState, std::shared_ptr<State>> m_states;
};

}   // namespace gui