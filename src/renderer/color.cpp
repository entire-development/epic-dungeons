#include "color.h"
#include <cassert>
#include <sstream>

namespace graphics {
Color::Color(const std::string &hex_str) {
    assert(hex_str[0] == '#' && (hex_str.size() == 7 || hex_str.size() == 9)
           && std::all_of(hex_str.begin() + 1, hex_str.end(), isxdigit));

    std::stringstream ss;
    ss << hex_str.substr(1);

    uint32_t hex;
    ss >> std::hex >> hex;

    if (hex_str.size() == 7) {
        hex <<= 8;
        hex += 0xFF;
    }

    r = (hex & 0xFF000000) >> (8 * 3);
    g = (hex & 0x00FF0000) >> (8 * 2);
    b = (hex & 0x0000FF00) >> (8 * 1);
    a = (hex & 0x000000FF) >> (8 * 0);
}

Color::Color(const sf::Color &color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

Color::Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) : r(r), g(g), b(b), a(a) {}

sf::Color Color::toSF() const {
    return {r, g, b, a};
}
}   // namespace graphics