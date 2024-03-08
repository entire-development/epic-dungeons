#include "sprite.h"

namespace graphics {
    Sprite::Sprite(const std::string &name_sprite)
    {
        path = cfg::SPRITES_PATH+path;
    }
    Sprite &Sprite::setColor(const graphics::Color &sprite_color)
    {
        color = sprite_color;
        return *this;
    }
    Sprite &Sprite::setScale(float factorX, float factorY)
    {
        x_scale = factorX, y_scale = factorY;
        return *this;
    }
    Sprite &Sprite::setRotation(float rotation_angle)
    {
        angle = rotation_angle;
        return *this;
    }
    sf::Sprite Sprite::toSF() const
    {
        sf::Sprite sprite;
        sf::Texture texture;

        if (!texture.loadFromFile(path))
        {
            throw std::runtime_error("Error loading sprite from file: " + path);
        }
        sprite.setTexture(texture);
        sprite.setColor(color.toSF());
        sprite.setRotation(angle);
        sprite.setScale(x_scale, y_scale);
        return sprite;
    }
}

