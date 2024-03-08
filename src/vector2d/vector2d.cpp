#include "vector2d.h"
#include <cmath>
using namespace std;
Vector2d::Vector2d(double x, double y) : m_x(x), m_y(y) {};
Vector2d::Vector2d(sf::Vector2u vector) : m_x(vector.x), m_y(vector.y) {};

Vector2d Vector2d::operator+(const Vector2d &other) const {
    return Vector2d(m_x + other.m_x, m_y + other.m_y);
}

Vector2d Vector2d::operator-(const Vector2d &other) const {
    return Vector2d(m_x - other.m_x, m_y - other.m_y);
}

Vector2d Vector2d::operator-() const {
    return Vector2d(-m_x, -m_y);
}

Vector2d Vector2d::operator*(double b) const {
    return Vector2d(m_x * b, m_y * b);
}

Vector2d Vector2d::operator/(double b) const {
    return Vector2d(m_x / b, m_y / b);
}

Vector2d Vector2d::round() const {
    return Vector2d(roundf(m_x), roundf(m_y));
}

double Vector2d::length_squared() const {
    return pow(m_x, 2) + pow(m_y, 2);
}

double Vector2d::length() const {
    return sqrt(length_squared());
}

Vector2d Vector2d::normalized() const {
    return (*this) / length();
}

int Vector2d::manhattan_length() const {
    return std::round(fabs(m_x) + fabs(m_y));
}

double Vector2d::x() const {
    return m_x;
}

double Vector2d::y() const {
    return m_y;
}
