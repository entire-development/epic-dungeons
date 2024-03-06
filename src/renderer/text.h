#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "static_data/game_config.h"
#include "graphics.h"

namespace graphics
{
class Text {
public:
    Text(const std::string &text, const std::string &font_name, const uint &size, const Color &color);

    Text& setColor(const Color &color);
    Text& setOutlineColor(const Color &color);
    Text& setStyle(const sf::Uint32 style);
    Text& setRotation(float angle);
    Text& setLetterSpacing(float spacingFactor);
    Text& setScale(float factorX, float factorY);
    std::string getFont(const std::string &name) const;
    sf::Text toSF() const;

private:
    std::string line;
    std::string font;
    uint character_size;
    float text_angle;
    float letter_spacing;
    float x_scale;
    float y_scale;
    sf::Text text_style;
    Color text_color;
    Color outline_color;
};
}
