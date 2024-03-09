#include "timed_count.h"
#include <utility>

namespace gui {
void TimedCount::init(double from, double to, uint64_t time, std::function<double(double)> f) {
    _from = from;
    _to = to;
    _time = time;
    _f = std::move(f);
}

void TimedCount::start() {
    _cur_time = 0;
}

void TimedCount::update(uint64_t delta_time) {
    _cur_time += delta_time;
    if (_cur_time > _time) {
        _cur_time = _time;
    }
}

double TimedCount::get() {
    return _f(static_cast<double>(_cur_time) / static_cast<double>(_time)) * (_to - _from);
}
}   // namespace gui
