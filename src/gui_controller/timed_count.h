#pragma once
#include <functional>
#include <cstdint>

namespace gui {
class TimedCount {
public:
    void init(float from, float to, uint64_t time);

    void init(float from, float to, uint64_t time, std::function<float(float)> f);

    void start();
    void update(uint64_t delta_time);

    float get() const;

    bool isEnded() const;

private:
    float m_from, m_to;
    uint64_t m_time;
    uint64_t m_cur_time;
    std::function<float(float)> m_f;
};
}   // namespace gui
