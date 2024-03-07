#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "static_data/game_config.h"
#include "graphics.h"

namespace graphics
{
class Text {
public:
    Text(const std::string &text, const std::string &font_name, const uint &size);

    Text& setColor(const Color &color);
    Text& setOutlineColor(const Color &color);
    Text& setOutlineThickness(float thickness);
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
    float text_angle = 0.f;
    float letter_spacing = 1;
    float x_scale = 1.0f;
    float y_scale = 1.0f;
    float outline_thickness = 0;
    sf::Text text_style;
    Color text_color = Color("#ffffff");
    Color outline_color = Color("#000000");
};
}
