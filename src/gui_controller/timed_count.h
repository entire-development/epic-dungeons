#pragma once
#include <functional>

class TimedCount {
public:
    void init(
        double from, double to, uint64_t time, std::function<double(double)> f = [](double x) {
            return x;
        });

    void start();
    void update(uint64_t delta_time);

    double get();

private:
    double _from, _to;
    uint64_t _time;
    uint64_t _cur_time;
    std::function<double(double)> _f;
};
