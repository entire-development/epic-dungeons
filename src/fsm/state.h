#pragma once
#include "fsm.h"

namespace fsm {
template<typename States>
class StateMachine;

template<typename States>
class State {
    friend class StateMachine<States>;

public:
    virtual void enter(StateMachine<States> *fsm) = 0;
    virtual void update(StateMachine<States> *fsm) = 0;
    virtual void exit(StateMachine<States> *fsm) = 0;
};

}   // namespace fsm