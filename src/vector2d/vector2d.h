#pragma once
#include <iostream>

class vector2d {
public:
    vector2d();
    vector2d(double x, double y);
    vector2d(long x, long y);
    vector2d(int x, int y);
    vector2d operator+(vector2d b);
    vector2d operator-(vector2d b);
    vector2d operator-();
    vector2d operator*(double b);
    vector2d operator*(long b);
    vector2d operator*(int b);
    vector2d operator/(double b);
    vector2d operator/(long b);
    vector2d operator/(int b);
    vector2d round();
    double lenght_squared();
    double lenght();
    vector2d normalized();
    int manhattan_lenght();

private:
    double x, y;
};
