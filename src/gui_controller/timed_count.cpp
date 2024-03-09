#include "timed_count.h"
#include <utility>

namespace gui {
void TimedCount::init(double from, double to, uint64_t time) {
    m_from = from;
    m_to = to;
    m_time = time;
    m_f = [](double x) {
        return x;
    };
}

void TimedCount::init(double from, double to, uint64_t time, std::function<double(double)> f) {
    m_from = from;
    m_to = to;
    m_time = time;
    m_f = std::move(f);
}

void TimedCount::start() {
    m_cur_time = 0;
}

void TimedCount::update(uint64_t delta_time) {
    m_cur_time += delta_time;
    if (m_cur_time > m_time) {
        m_cur_time = m_time;
    }
}

double TimedCount::get() const {
    return m_f(static_cast<double>(m_cur_time) / static_cast<double>(m_time)) * (m_to - m_from);
}
}   // namespace gui
