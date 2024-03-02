#pragma once
#include "renderer/irenderer.h"
#include "SFML/Graphics.hpp"
#include "keyboard//keyboard.h"
#include <iostream>
#include <map>

namespace Renderer {
    struct Rectangle {
        float x;
        float y;
        float w;
        float h;
        uint64_t color = 0xffffffff; // this type is temporary! later I will write a wholesome Color class.
        float stroke = 0;
        uint64_t stroke_color = 0x000000ff;
    };

    class SFMLRenderer : public IRenderer {
    public:
        // constructor
        SFMLRenderer();

        void drawCanvas() override;
        void updateState(uint64_t deltatime) override;

        void drawSprite(int x, int y, std::string sprite_id) override;

        void drawRec(Rectangle rectangle);

        void drawText(int x, int y, std::string line) override;

    private:
        sf::RenderWindow window;

        Keyboard::Key handleSFMLKey(sf::Keyboard::Key key);
    };
}
