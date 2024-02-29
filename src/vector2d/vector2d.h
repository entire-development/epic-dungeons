#pragma once

class Vector2d {
public:
    Vector2d(double x, double y);
    Vector2d operator+(const Vector2d &other) const;
    Vector2d operator-(const Vector2d &other) const;
    Vector2d operator-() const;
    Vector2d operator*(double b) const;
    Vector2d operator/(double b) const;
    Vector2d round() const;
    double length_squared() const;
    double length() const;
    Vector2d normalized() const;
    int manhattan_length() const;

private:
    double x, y;
};
