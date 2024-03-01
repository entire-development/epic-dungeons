#pragma once
#include "view/renderer/irenderer/irenderer.h"
#include <SFML/Graphics.hpp>
#include "game-config.h"

class SFMLRenderer : public IRenderer {
    public:
        // constructor
        SFMLRenderer();

        KeyboardEvent update(uint64_t deltatime) override;
        int draw_sprite(int x, int y, std::string sprite_id) override;
        int draw_rec(int x, int y, int w, int h, std::string color="#000000", std::string stroke_color="NONE", int stroke_weight=0) override;
        int draw_text(int x, int y, std::string line) override;

        // destructors
        // ~SFMLRenderer() {};
    private:
        sf::RenderWindow window;
};

