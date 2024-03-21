#include "sprite.h"
#include "logging/logger.h"

namespace graphics {
Sprite::Sprite(const std::string &path) {
    m_path = cfg::SPRITES_PATH + path;
    if (!m_texture.loadFromFile(m_path)) {
        logging::error("Error loading sprite from file: " + m_path);
        throw std::runtime_error("Error loading sprite from file: " + m_path);
    }
    logging::debug("Loaded sprite " + m_path);
    m_texture.setSmooth(true);   // enable smooth texture
}

Sprite &Sprite::setColor(const graphics::Color &color) {
    m_color = color;
    return *this;
}

Sprite &Sprite::setScale(float factorX, float factorY) {
    m_x_scale = factorX, m_y_scale = factorY;
    return *this;
}

Vector2d Sprite::getScale() const {
    return Vector2d(m_x_scale, m_y_scale);
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
    float x_scale = m_flipped_x ? -m_x_scale : m_x_scale;
    float y_scale = m_flipped_y ? -m_y_scale : m_y_scale;
    float origin_x = 0;
    float origin_y = 0;
    if (m_flipped_x)
        origin_x = m_texture.getSize().x;
    sprite.setOrigin(origin_x, origin_y);
    sprite.setScale(x_scale, y_scale);
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

Sprite &Sprite::flipX() {
    m_flipped_x = !m_flipped_x;
    return *this;
}

Sprite &Sprite::flipY() {
    m_flipped_y = !m_flipped_y;
    return *this;
}

Sprite &Sprite::setFlip(bool flipX, bool flipY) {
    m_flipped_x = flipX;
    m_flipped_y = flipY;
    return *this;
}

Sprite &Sprite::toSize(const float &x, const float &y) {
    setScale(x / m_texture.getSize().x, y / m_texture.getSize().y);
    return *this;
}

}   // namespace graphics
