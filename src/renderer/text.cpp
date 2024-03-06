#include "text.h"

using namespace graphics;

graphics::Text::Text(const std::string &text, const std::string &font_name, const uint &size) {
    line = text;
    font = font_name;
    character_size = size;
}

std::string graphics::Text::getFont(const std::string &name) const {
    std::string font = "epic-dungeons/res/fonts/" + name + ".ttf";
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

    return text;
}
