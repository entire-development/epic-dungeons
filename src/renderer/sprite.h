#pragma once
#include "color.h"
#include "static_data/game_config.h"
#include <iostream>

namespace graphics {
    class Sprite 
    {
        public:
            Sprite(const std::string &path);
            Sprite& setColor(const graphics::Color &sprite_color);
            Sprite& setScale(float factorX, float factorY);
            Sprite& setRotation(float angle);
            sf::Sprite toSF() const;
        private:
            std::string path;
            float x_scale = 1.0f, y_scale = 1.0f, angle = 0;
            graphics::Color color = "#000000";
    };
}