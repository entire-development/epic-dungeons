#pragma once
#include "logging/logger.h"
#include "state.h"

#include <map>
#include <string>

namespace fsm {

template <typename... Args> class StateMachine {
public:
    /// @brief StateMachine constructor
    /// It starts with state "start" and ends with state "end" (if ends)
    /// "start" and "end" are reserved words and used for routing to child state machines
    StateMachine() : m_states() {}

    /// @brief Update the state machine, calling the update function of the current state
    /// and changing the current state to the returned state
    void update(Args... args) {
        logging::debug("StateMachine::update: current state: " + m_current_state);
        auto state = m_states[m_current_state];
    std:
        m_current_state = state.first + state.second->update(args...);
        logging::debug("StateMachine::update: new state: " + m_current_state);
    }

    /// @brief Add a state to the state machine
    void addState(State<Args...> *state) {
        logging::debug("StateMachine::addState: " + state->getName());
        m_states[state->getName()] = {"", state};
        state->m_machine = this;
    }

    /// @brief include StateMachine as state
    /// it must has entrypoint "start" and exitpoint "end"
    void addSubMachine(const std::string &name, StateMachine<Args...> *machine) {
        // add start and end states
        addState(new RedirectState<Args...>(name, name + ".start"));
        logging::debug("StateMachine::addSubMachine: " + name);
        for (auto &state : machine->m_states) {
            logging::debug("StateMachine::addSubMachine: " + state.first);
            std::string new_state_name = name + "." + state.first;
            std::string new_state_prefix = state.second->first + name + ".";
            m_states[new_state_name] = {new_state_prefix, state.second->second};
            state.second->m_machine = this;
        }
    }

private:
    std::map<std::string, std::pair<std::string, State<Args...> *>> m_states;
    std::string m_current_state = "start";
};

} // namespace fsm