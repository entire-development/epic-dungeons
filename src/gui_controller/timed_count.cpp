#include "timed_count.h"

TimedCount::TimedCount(double from, double to, uint64_t time, std::function<double(double)> f) :
    from(from), to(to), time(time), f(f) {}

void TimedCount::start() {
    cur_time = 0;
}

void TimedCount::update(uint64_t delta_time) {
    cur_time += delta_time;
    if (cur_time > time) {
        cur_time = time;
    }
}

double TimedCount::get() {
    return (cur_time / time) * (to - from);
}
