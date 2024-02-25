#pragma once
#include <vector>

class Action {
public:
    virtual void execute() = 0;
};


class Event {
public:
    Event();
    void execute();
private:
    std::vector<Action *> _actions;
};
