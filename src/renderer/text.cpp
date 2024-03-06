#include "text.h"

using namespace graphics;

graphics::Text::Text(const std::string &text, const std::string &font_name, const uint &size) {
    line = text;
    font = font_name;
    character_size = size;
}

Text &graphics::Text::setColor(const Color &color) {
    text_color = color;
    return *this;
}

Text &graphics::Text::setOutlineColor(const Color &color) {
    outline_color = color;
    return *this;
}

Text &graphics::Text::setOutlineThickness(float thickness) {
    outline_thickness = thickness;
    return *this;
}

Text &graphics::Text::setStyle(const sf::Uint32 style) {
    text_style.setStyle(style);
    return *this;
}

Text &graphics::Text::setRotation(float angle) {
    text_angle = angle;
    return *this;
}

Text &graphics::Text::setLetterSpacing(float spacing_factor) {
    letter_spacing = spacing_factor;
    return *this;
}

Text &graphics::Text::setScale(float factorX, float factorY) {
    x_scale = factorX;
    y_scale = factorY;
    return *this;
}

std::string graphics::Text::getFont(const std::string &name) const {
    std::string font = cfg::FONT_PATH + name + ".ttf";
    return font;
}

sf::Text graphics::Text::toSF() const {
    sf::Font text_font;
    if (!text_font.loadFromFile(getFont(font))) {
        throw std::runtime_error("Error loading font from file: " + font);
    }

    sf::Text text;
    text.setFont(text_font);
    text.setString(line);
    text.setCharacterSize(character_size);
    text.setFillColor(text_color.getSFColor());
    text.setOutlineColor(outline_color.getSFColor());
    text.setOutlineThickness(outline_thickness);
    text.setStyle(text_style.getStyle());
    text.setRotation(text_angle);
    text.setLetterSpacing(letter_spacing);
    text.setScale(x_scale, y_scale);

    return text;
}
