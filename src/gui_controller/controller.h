#pragma once
#include "engine/engine.h"
#include "renderer/sfml_renderer/sfml_renderer.h"

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
    Controller(renderer::SFMLRenderer &renderer, engine::Engine &engine);

    template<typename T>
    void addState(const GUIState &state) {
        m_states[state] = std::make_shared<T>();
    }

    void changeState(const GUIState &state) {
        if (m_current_state) {
            m_current_state->exit(this);
        }
        m_current_state = m_states[state];
        m_current_state->enter(this);
    }

    void update() {
        if (m_current_state) {
            m_current_state->update(this);
        }
    }

    renderer::SFMLRenderer &m_renderer;
    engine::Engine &m_engine;

protected:
    std::shared_ptr<State> m_current_state;
    std::map<GUIState, std::shared_ptr<State>> m_states;
};

}   // namespace gui