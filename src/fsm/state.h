#pragma once
#include "fsm.h"

namespace fsm {

template <class States> class StateMachine;

template <class States> class State {
public:
    virtual void enter(StateMachine<States> *fsm) = 0;
    virtual void update(StateMachine<States> *fsm) = 0;
    virtual void exit(StateMachine<States> *fsm) = 0;

private:
    friend class StateMachine<States>;
    State(const States &state) : m_state(state) {}
    virtual ~State() = default;
    const States m_state;
};

} // namespace fsm