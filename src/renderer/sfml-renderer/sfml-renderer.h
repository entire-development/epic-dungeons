#pragma once
#include "renderer/irenderer/irenderer.h"
#include "SFML/Graphics.hpp"
#include "input/input.h"

namespace Renderer {
    class SFMLRenderer : public IRenderer {
    public:
        // constructor
        SFMLRenderer();

        Input::KeyboardEvent update(uint64_t deltatime) override;

        int drawSprite(int x, int y, std::string sprite_id) override;

        int drawRec(int x, int y, int w, int h, std::string color = "#000000", std::string stroke_color = "NONE",
                    int stroke_weight = 0) override;

        int drawText(int x, int y, std::string line) override;

    private:
        sf::RenderWindow window;
    };
}
