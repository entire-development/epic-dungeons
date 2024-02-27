#pragma once
#include "fsm.h"
#include <functional>
#include <iostream>
#include <string>

namespace fsm {
template <typename... Args> class StateMachine;

/// @brief StateMachine state
template <typename... Args> class State {
public:
    State(const std::string &name) : m_name(name) {}
    const std::string &getName() const { return m_name; }

    // @brief Run the state and return the next state
    virtual const std::string update(Args... args) { return m_name; }

    /// @brief allow StateMachine to access private members
    friend class StateMachine<Args...>;

protected:
    const std::string &m_name;
    /// @brief StateMachine which contains this state
    StateMachine<Args...> *m_machine;
};

/// @brief State builder from function
template <typename... Args> class FuncState : public State<Args...> {
public:
    FuncState(const std::string &name, std::function<std::string(Args...)> update)
        : State<Args...>(name), m_update(update) {}

    const std::string update(Args... args) override { return m_update(args...); }

private:
    std::function<std::string(Args...)> m_update;
};

/// @brief State builder redirecting to another state
template <typename... Args> class RedirectState : public State<Args...> {
public:
    RedirectState(const std::string &from, const std::string &to) : State<Args...>(from), m_redirect(to) {}

    const std::string update(Args... args) override { return m_redirect; }

private:
    const std::string &m_redirect;
};

} // namespace fsm