#pragma once
#include <SFML/System/Vector2.hpp>

class Vector2d {
public:
    Vector2d(float x, float y);
    Vector2d(sf::Vector2u vector);
    Vector2d operator+(const Vector2d &other) const;
    Vector2d operator-(const Vector2d &other) const;
    Vector2d operator-() const;
    Vector2d operator*(float b) const;
    Vector2d operator/(float b) const;
    Vector2d round() const;
    float x() const;
    float y() const;
    float length_squared() const;
    float length() const;
    Vector2d normalized() const;
    int manhattan_length() const;

private:
    float m_x, m_y;
};
