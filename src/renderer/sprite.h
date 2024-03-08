#pragma once
#include "color.h"
#include "static_data/game_config.h"
#include "vector2d/vector2d.h"
#include <iostream>

namespace graphics {
class Sprite {
public:
    Sprite(const std::string &path);
    Sprite &setColor(const graphics::Color &color);
    Sprite &setScale(float factorX, float factorY);
    Sprite &setScale(float ratio);
    Sprite &setRotation(float angle);
    Sprite &toSizeY(const float &y);
    Sprite &toSizeX(const float &x);
    Sprite &toSize(const float &x, const float &y);
    sf::Sprite toSF() const;
    Vector2d getSize() const;

private:
    std::string m_path;
    float m_x_scale = 1.0f, m_y_scale = 1.0f, m_angle = 0;
    graphics::Color m_color = "#FFFFFF";
    mutable sf::Texture m_texture;
};
}   // namespace graphics
