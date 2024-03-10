#include "timed_count.h"
#include <utility>

namespace gui {
void TimedCount::init(float from, float to, uint64_t time) {
    m_from = from;
    m_to = to;
    m_time = time;
    m_f = [](float x) {
        return x;
    };
}

void TimedCount::init(float from, float to, uint64_t time, std::function<float(float)> f) {
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

float TimedCount::get() const {
    return m_from + m_f(static_cast<float>(m_cur_time) / static_cast<float>(m_time)) * (m_to - m_from);
}

bool TimedCount::isEnded() const {
    return m_cur_time == m_time;
}
}   // namespace gui
