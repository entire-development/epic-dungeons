#pragma once
#include <cstdint>
#include <functional>
#include <cstdint>

namespace gui {

//std::function<float(uint32_t)> frame_func(uint32_t frame_count, uint32_t cycle_len) { // function to animate sprites with frames
//    return [&cycle_len, &frame_count](float x) {
//        return (std::lround(x) % cycle_len) / frame_count;
//    };
//}

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
