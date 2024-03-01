#pragma once
#include "fsm/state.h"
#include <map>
#include <memory>

namespace fsm {

template <typename States> class StateMachine {
public:
    template <typename State> void addState(const States &state) { m_states[state] = std::make_shared<State>(state); }

    void changeState(const States &state) {
        if (m_current_state) { m_current_state->exit(this); }
        m_current_state = m_states[state];
        m_current_state->enter(this);
    }

    void update() {
        if (m_current_state) { m_current_state->update(this); }
    }

protected:
    std::shared_ptr<State<States>> m_current_state;

private:
    std::map<States, std::shared_ptr<State<States>>> m_states;
};

} // namespace fsm