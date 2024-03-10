#pragma once
#include <functional>

namespace gui {
class TimedCount {
public:
    void init(double from, double to, uint64_t time);

    void init(
        double from, double to, uint64_t time, std::function<double(double)> f = [](double x) {
            return x;
        });

    void start();
    void update(uint64_t delta_time);

    double get() const;

    bool isEnded() const;

private:
    double m_from, m_to;
    uint64_t m_time;
    uint64_t m_cur_time;
    std::function<double(double)> m_f;
};
}   // namespace gui
