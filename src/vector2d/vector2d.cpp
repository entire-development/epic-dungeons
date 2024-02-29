#include "vector2d.h"
#include <cmath>
using namespace std;
Vector2d::Vector2d(double x, double y) : x(x), y(y){};
const Vector2d Vector2d::operator+(const Vector2d &other) {
    return Vector2d(x + other.x, y + other.y);
}
const Vector2d Vector2d::operator-(const Vector2d &other) {
    return Vector2d(x - other.x, y - other.y);
}
const Vector2d Vector2d::operator-() {
    return Vector2d(-x, -y);
}
const Vector2d Vector2d::operator*(double b) {
    return Vector2d(x * b, y * b);
}
const Vector2d Vector2d::operator/(double b) {
    return Vector2d(x / b, y / b);
}
const Vector2d Vector2d::round() {
    return Vector2d(roundf(x), roundf(y));
}
const double Vector2d::length_squared() {
    return pow(x, 2) + pow(y, 2);
}
const double Vector2d::length() {
    return sqrt(length_squared());
}
const Vector2d Vector2d::normalized() {
    return (*this) / length();
}
const int Vector2d::manhattan_length() {
    return std::round(fabs(x) + fabs(y));
}
