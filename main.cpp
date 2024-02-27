#include "fsm/fsm.h"
#include <iostream>

int main() {
    fsm::StateMachine<char> state_machine = fsm::StateMachine<char>();

    state_machine.addState(new fsm::RedirectState<char>("start", "a"));

    state_machine.addState(new fsm::FuncState<char>("a", [](char c) {
        std::cout << "State a" << std::endl;
        if (c == 'a') { return "b"; }
        return "a";
    }));

    state_machine.addState(new fsm::FuncState<char>("b", [](char c) {
        std::cout << "State b" << std::endl;
        if (c == 'b') { return "a"; }
        return "b";
    }));

    state_machine.update('a');
    state_machine.update('a');
    state_machine.update('a');

    return 0;
}