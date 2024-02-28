#include "vector2d.h"
#include <cmath>
using namespace std;
Vector2d::Vector2d(double x, double y) : x(x), y(y){};
Vector2d Vector2d::operator+(Vector2d b) {
    return Vector2d(x + b.x, y + b.y);
}
Vector2d Vector2d::operator-(Vector2d b) {
    return Vector2d(x - b.x, y - b.y);
}
Vector2d Vector2d::operator-() {
    return Vector2d(-x, -y);
}
Vector2d Vector2d::operator*(double b) {
    return Vector2d(x * b, y * b);
}
Vector2d Vector2d::operator/(double b) {
    return Vector2d(x / b, y / b);
}
Vector2d Vector2d::round() {
    return Vector2d(roundf(x), roundf(y));
}
double Vector2d::lenght_squared() {
    return x + y;
}
double Vector2d::lenght() {
    return sqrt(lenght_squared());
}
Vector2d Vector2d::normalized() {
    return (*this) / lenght();
}
int Vector2d::manhattan_lenght() {
    return std::round(fabs(x) + fabs(y));
}
