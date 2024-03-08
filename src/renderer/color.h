#pragma once
#include "SFML/Graphics.hpp"
#include <cstdint>

namespace graphics {
class Color {
public:
    Color(const std::string &hex_str);

    Color(const char *hex_str) : Color(std::string(hex_str)) {}

    Color(const sf::Color &color);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    [[nodiscard]] sf::Color toSF() const;

    [[nodiscard]] uint8_t getR() const {
        return r;
    };

    [[nodiscard]] uint8_t getG() const {
        return g;
    };

    [[nodiscard]] uint8_t getB() const {
        return b;
    };

    [[nodiscard]] uint8_t getA() const {
        return a;
    };

private:
    uint8_t r;   // red
    uint8_t g;   // green
    uint8_t b;   // blue
    uint8_t a;   // alpha
};

}   // namespace graphics