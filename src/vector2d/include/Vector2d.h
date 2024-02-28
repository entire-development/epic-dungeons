#pragma once
#include <iostream>

class vector2d {
public:
    vector2d();
    vector2d(double x1, double y1);
    vector2d(long x1, long y1);
    vector2d(int x1, int y1);
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
    double x1, y1, x2, y2;
};
