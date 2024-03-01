#pragma once
#include "renderer/irenderer/irenderer.h"
#include "SFML/Graphics.hpp"
#include "input/input.h"
#include <iostream>
#include <map>

namespace Renderer {
    struct Rectangle {
        float x;
        float y;
        float w;
        float h;
        uint64_t color; // this type is temporary! later I will write a wholesome Color class.
        float stroke;
        uint64_t stroke_color;
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
        std::map<Input::Controls, sf::Keyboard::Key> SFMLControls = {
                { Input::Controls::MOVE_TOP, sf::Keyboard::Up },
                { Input::Controls::MOVE_RIGHT, sf::Keyboard::Right },
                { Input::Controls::MOVE_DOWN, sf::Keyboard::Down },
                { Input::Controls::MOVE_LEFT, sf::Keyboard::Left },
                { Input::Controls::ACTION, sf::Keyboard::Z },
                { Input::Controls::CLOSE, sf::Keyboard::X },
                { Input::Controls::SECONDARY, sf::Keyboard::C },
        };
        sf::RenderWindow window;
    };
}
