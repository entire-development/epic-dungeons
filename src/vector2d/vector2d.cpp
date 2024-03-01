#include "vector2d.h"
#include <cmath>
using namespace std;
Vector2d::Vector2d(double x, double y) : x(x), y(y){};
Vector2d Vector2d::operator+(const Vector2d &other) const {
    return Vector2d(x + other.x, y + other.y);
}
Vector2d Vector2d::operator-(const Vector2d &other) const {
    return Vector2d(x - other.x, y - other.y);
}
Vector2d Vector2d::operator-() const {
    return Vector2d(-x, -y);
}
Vector2d Vector2d::operator*(double b) const {
    return Vector2d(x * b, y * b);
}
Vector2d Vector2d::operator/(double b) const {
    return Vector2d(x / b, y / b);
}
Vector2d Vector2d::round() const {
    return Vector2d(roundf(x), roundf(y));
}
double Vector2d::length_squared() const {
    return pow(x, 2) + pow(y, 2);
}
double Vector2d::length() const {
    return sqrt(length_squared());
}
Vector2d Vector2d::normalized() const {
    return (*this) / length();
}
int Vector2d::manhattan_length() const {
    return std::round(fabs(x) + fabs(y));
}
