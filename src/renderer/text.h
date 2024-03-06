#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

namespace graphics
{
class Text {
public:
    Text(const std::string &text, const std::string &font_name, const uint &size);
    std::string getFont(const std::string &name) const;
    sf::Text toSF() const;

private:
    std::string line;
    std::string font;
    uint character_size;
};
}
