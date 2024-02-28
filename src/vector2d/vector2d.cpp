#include "vector2d.h"
#include <cmath>
using namespace std;
Vector2d::Vector2d(double x, double y) : x(x), y(y){};
Vector2d Vector2d::operator+(Vector2d b) {
    return Vector2d((*this).x + b.x, (*this).y + b.y);
}
Vector2d Vector2d::operator-(Vector2d b) {
    return Vector2d((*this).x - b.x, (*this).y - b.y);
}
Vector2d Vector2d::operator-() {
    return Vector2d(-(*this).x, -(*this).y);
}
Vector2d Vector2d::operator*(double b) {
    return Vector2d((*this).x * b, (*this).y * b);
}
Vector2d Vector2d::operator/(double b) {
    return Vector2d((*this).x / b, (*this).y / b);
}
Vector2d Vector2d::round() {
    return Vector2d(roundf((*this).x), roundf((*this).y));
}
double Vector2d::lenght_squared() {
    return x + y;
}
double Vector2d::lenght() {
    return sqrt(lenght_squared());
}
Vector2d Vector2d::normalized() {
    return (*this) / (*this).lenght();
}
int Vector2d::manhattan_lenght() {
    return std::round(fabs((*this).x) + fabs((*this).y));
}
