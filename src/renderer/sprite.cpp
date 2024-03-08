#include "sprite.h"

namespace graphics {
Sprite::Sprite(const std::string &path) {
    m_path = cfg::SPRITES_PATH + path;
}

Sprite &Sprite::setColor(const graphics::Color &color) {
    m_color = color;
    return *this;
}

Sprite &Sprite::setScale(float factorX, float factorY) {
    m_x_scale = factorX, m_y_scale = factorY;
    return *this;
}

Sprite &Sprite::setScale(float ratio) {
    m_x_scale = ratio, m_y_scale = ratio;
    return *this;
}

Sprite &Sprite::setRotation(float rotation_angle) {
    m_angle = rotation_angle;
    return *this;
}

sf::Sprite Sprite::toSF() const {
    sf::Sprite sprite;
    if (!m_texture.loadFromFile(m_path)) {
        throw std::runtime_error("Error loading sprite from file: " + m_path);
    }
    sprite.setTexture(m_texture);
    sprite.setColor(m_color.toSF());
    sprite.setRotation(m_angle);
    sprite.setScale(m_x_scale, m_y_scale);
    return sprite;
}

Vector2d Sprite::getSize() const {
    return Vector2d(m_texture.getSize());
}

Sprite &Sprite::toSizeX(const float &x) {
    float ratio = x / getSize().x();
    m_x_scale *= ratio;
    m_y_scale *= ratio;
    return *this;
}

Sprite &Sprite::toSizeY(const float &y) {
    float ratio = y / getSize().y();
    m_x_scale *= ratio;
    m_y_scale *= ratio;
    return *this;
}

Sprite &Sprite::toSize(const float &x, const float &y) {
    Vector2d tmp = getSize();
    m_x_scale *= x / tmp.x();
    m_y_scale *= y / tmp.y();
    return *this;
}
}   // namespace graphics
