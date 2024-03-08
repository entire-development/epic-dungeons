#include "sprite.h"

namespace graphics {
Sprite::Sprite(const std::string &path) {
    m_path = cfg::SPRITES_PATH + path;
    if (!m_texture.loadFromFile(m_path)) {
        throw std::runtime_error("Error loading sprite from file: " + m_path);
    }
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
    sprite.setTexture(m_texture);
    sprite.setColor(m_color.toSF());
    sprite.setRotation(m_angle);
    sprite.setScale(m_x_scale, m_y_scale);
    return sprite;
}

Vector2d Sprite::getSize() const {
    sf::Vector2u vector = m_texture.getSize();
    vector.x *= m_x_scale;
    vector.y *= m_y_scale;
    return Vector2d(vector);
}

Sprite &Sprite::toSizeX(const float &x) {
    setScale(x / m_texture.getSize().x);
    return *this;
}

Sprite &Sprite::toSizeY(const float &y) {
    setScale(y / m_texture.getSize().y);
    return *this;
}

Sprite &Sprite::toSize(const float &x, const float &y) {
    setScale(x / m_texture.getSize().x, y / m_texture.getSize().y);
    return *this;
}
}   // namespace graphics
