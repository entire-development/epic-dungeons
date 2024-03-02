#pragma once
#include "SFML/Graphics.hpp"
#include "keyboard//keyboard.h"
#include "renderer/irenderer.h"
#include <iostream>
#include <map>

namespace Renderer {
class Color {
public:
    Color(const std::string &hex_str);
    Color(const uint32_t &hex);
    Color(const sf::Color &color);
    const std::string toHexString() const;
    const sf::Color getSFColor() const;

private:
    sf::Color sfcolor;
};

struct Rectangle {
    float x;
    float y;
    float w;
    float h;
    Color color = 0xffffffff;   // this type is temporary! later I will write a wholesome Color class.
    float stroke = 0;
    Color stroke_color = 0x000000ff;
};

class SFMLRenderer : public IRenderer {
public:
    // constructor
    SFMLRenderer(sf::RenderWindow &window);

    void drawCanvas() override;
    void updateState(uint64_t deltatime) override;

    void drawSprite(int x, int y, const std::string &sprite_id) override;

    void drawRec(const Rectangle &rectangle);

    void drawText(int x, int y, const std::string &line) override;

private:
    sf::RenderWindow &window;
};
}   // namespace Renderer
