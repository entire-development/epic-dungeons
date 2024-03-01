#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

struct KeyboardEvent {
    uint8_t type;
    uint8_t code;
};

class IRenderer {
    public:
        // constructors
        IRenderer();

        // call on game initialization
        virtual void start();

        // call in main event loop. Updates the screen. IDK is it good idea to implement it with double, but why not
        virtual KeyboardEvent update(uint64_t deltatime) = 0;

        // close window at program finish
        virtual void close();

        // call do draw specific image and its current animation frame
        virtual int drawSprite(int x, int y, std::string sprite_id) = 0;

        // call to draw rectangle
        virtual int drawRec(int x, int y, int w, int h, std::string color="#000000", std::string stroke_color="NONE", int stroke_weight=0) = 0;

        // call to draw
        virtual int drawText(int x, int y, std::string line) = 0;

        // check if is active
        virtual bool isActive ();

        // get previous keyboard event
        KeyboardEvent getPrevKeyboardEvent() ;

        // destructor
        virtual ~IRenderer() = default;

    protected:
        // looped timer that will be later used in animation rendering
        uint64_t animation_timer;

        // activity status
        bool active;

        // previous keyboard event
        KeyboardEvent prev_keyboard_event;
};
