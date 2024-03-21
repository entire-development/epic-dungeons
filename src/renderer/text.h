#pragma once
#include "SFML/Graphics/Color.hpp"
#include "color.h"
#include "static_data/game_config.h"
#include "vector2d/vector2d.h"
#include <iostream>

namespace graphics {
class Color;

class Text {
public:
    Text(const std::string &text, const std::string &font_name = cfg::FONT_PATH, const size_t &size = cfg::DIALOGUE_FONT_SIZE);

    enum class Origin {
        CENTER,
        TOP_LEFT,
        BOTTOM_LEFT,
    };

    Text &setColor(const graphics::Color &color);
    Text &setOutlineColor(const Color &color);
    Text &setOutlineThickness(float thickness);
    Text &setStyle(const sf::Uint32 style);
    Text &setRotation(float angle);
    Text &setLetterSpacing(float spacingFactor);
    Text &setScale(float factorX, float factorY);
    Vector2d getSize() const;
    Text &setFontSize(int size);
    std::string getFont(const std::string &name) const;
    sf::Text toSF() const;

private:
    std::string line;
    std::string font;
    size_t character_size;
    float text_angle = 0.f;
    float letter_spacing = 1;
    float x_scale = 1.0f;
    float y_scale = 1.0f;
    float outline_thickness = 0;
    sf::Text text_style;
    graphics::Color text_color = "#ffffff";
    graphics::Color outline_color = "#000000";
    mutable sf::Font text_font;
};
}   // namespace graphics
