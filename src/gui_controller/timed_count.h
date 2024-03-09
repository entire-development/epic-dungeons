#pragma once
#include <functional>

class TimedCount {
public:
    TimedCount(
        double from, double to, uint64_t time, std::function<double(double)> f = [](double x) {
            return x;
        });

    void start();
    void update(uint64_t delta_time);

    double get();

private:
    double from, to;
    uint64_t time;
    uint64_t cur_time;
    std::function<double(double)> f;
};
