#include "Vector2d.h"
#include <cmath>
using namespace std;
vector2d::vector2d() {
    x1 = 0, y1 = 0;
}
vector2d::vector2d(double x1, double y1) {
    (*this).x1 = x1, (*this).y1 = y1;
}
vector2d::vector2d(long x1, long y1) {
    (*this).x1 = x1, (*this).y1 = y1;
}
vector2d::vector2d(double x1, double y1) {
    (*this).x1 = x1, (*this).y1 = y1;
}
vector2d vector2d::operator+(vector2d b) {
    return vector2d((*this).x1 + b.x1, (*this).y1 + b.y1);
}
vector2d vector2d::operator-(vector2d b) {
    return vector2d((*this).x1 - b.x1, (*this).y1 - b.y1);
}
vector2d vector2d::operator-() {
    return vector2d(-(*this).x1, -(*this).y1);
}
vector2d vector2d::operator*(double b) {
    return vector2d((*this).x1 * b, (*this).y1 * b);
}
vector2d vector2d::operator*(long b) {
    return vector2d((*this).x1 * b, (*this).y1 * b);
}
vector2d vector2d::operator*(int b) {
    return vector2d((*this).x1 * b, (*this).y1 * b);
}
vector2d vector2d::operator/(double b) {
    return vector2d((*this).x1 / b, (*this).y1 / b);
}
vector2d vector2d::round() {
    return vector2d(roundf((*this).x1), roundf((*this).y1));
}
double vector2d::lenght_squared() {
    return x1 + y1;
}
double vector2d::lenght() {
    return sqrt(lenght_squared());
}
vector2d vector2d::normalized() {
    return (*this) / (*this).lenght();
}
int vector2d::manhattan_lenght() {
    return std::round(fabs((*this).x1) + fabs((*this).y1));
}
