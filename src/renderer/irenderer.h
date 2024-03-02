#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "keyboard/keyboard.h"

namespace Renderer {
    class IRenderer {
    public:
        // constructors
        IRenderer();

        // call on game initialization
        virtual void start();

        // updates inputs, deltatime, clears old canvas. Should be called at the start of event loop iteration.
        virtual void updateState(uint64_t deltatime) = 0;

        // draws all objects on the canvas. Should be called at the end of event loop iteration.
        virtual void drawCanvas() = 0;

        // close window at program finish
        virtual void finish();

        // call do draw specific image and its current animation frame
        virtual void drawSprite(int x, int y, std::string sprite_id) = 0;

        // call to draw rectangle
//        virtual void
//        drawRec(int x, int y, int w, int h, std::string color = "#000000", std::string stroke_color = "NONE",
//                int stroke_weight = 0);

        // call to draw
        virtual void drawText(int x, int y, std::string line) = 0;

        // check if is active
        virtual bool isActive();

        // destructor
        virtual ~IRenderer() = default;

    protected:
        // looped timer that will be later used in animation rendering
        uint64_t animation_timer;

        // activity status
        bool active;
    };
}