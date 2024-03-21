#include "text.h"
#include "vector2d/vector2d.h"

namespace graphics {

Text::Text(const std::string &text, const std::string &font_name, const size_t &size) {
    line = text;
    font = font_name;
    character_size = size;
}

Text &Text::setColor(const Color &color) {
    text_color = color;
    return *this;
}

Text &Text::setOutlineColor(const Color &color) {
    outline_color = color;
    return *this;
}

Text &Text::setOutlineThickness(float thickness) {
    outline_thickness = thickness;
    return *this;
}

Text &Text::setStyle(const sf::Uint32 style) {
    text_style.setStyle(style);
    return *this;
}

Text &Text::setRotation(float angle) {
    text_angle = angle;
    return *this;
}

Text &Text::setLetterSpacing(float spacing_factor) {
    letter_spacing = spacing_factor;
    return *this;
}

Text &Text::setScale(float factorX, float factorY) {
    x_scale = factorX;
    y_scale = factorY;
    return *this;
}

Text &Text::setFontSize(int size) {
    character_size = size;
    return *this;
}

std::string Text::getFont(const std::string &name) const {
    std::string font = cfg::FONTS_PATH + name + ".ttf";
    return font;
}

Vector2d Text::getSize() const {
    sf::Text text = toSF();
    sf::FloatRect rect = text.getLocalBounds();
    return Vector2d(rect.width, rect.height);
}

sf::Text Text::toSF() const {
    if (!text_font.loadFromFile(getFont(font))) {
        throw std::runtime_error("Error loading font from file: " + font);
    }

    sf::Text text;
    text.setFont(text_font);
    text.setString(line);
    text.setCharacterSize(character_size);
    text.setFillColor(text_color.toSF());
    text.setOutlineColor(outline_color.toSF());
    text.setOutlineThickness(outline_thickness);
    text.setStyle(text_style.getStyle());
    text.setRotation(text_angle);
    text.setLetterSpacing(letter_spacing);
    text.setScale(x_scale, y_scale);

    return text;
}
}   // namespace graphics
