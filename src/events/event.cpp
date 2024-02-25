#include "event.h"

void Event::execute() {
    for (auto action : _actions) {
        action->execute();
    }
}