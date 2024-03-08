#pragma once
#include "keyboard/keyboard.h"
#include <string>

namespace cfg {
const int FRAMERATE = 30;
const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 600;
const unsigned CELL_SIZE = 15;
const std::string WINDOW_NAME = "*EPIC DUNGEONS*";
const std::string FONTS_PATH = "res/fonts/";
const std::string SPRITES_PATH = "res/sprites/";

const keyboard::Key CONTROLS_MOVE_RIGHT = keyboard::Key::KEY_RIGHT;
const keyboard::Key CONTROLS_MOVE_DOWN = keyboard::Key::KEY_DOWN;
const keyboard::Key CONTROLS_MOVE_LEFT = keyboard::Key::KEY_LEFT;
const keyboard::Key CONTROLS_MOVE_UP = keyboard::Key::KEY_UP;
const keyboard::Key CONTROLS_ACTION = keyboard::Key::KEY_Z;
const keyboard::Key CONTROLS_CLOSE = keyboard::Key::KEY_X;
const keyboard::Key CONTROLS_SECONDARY = keyboard::Key::KEY_C;

// !! Later put fonts into epic-dungeons/res/fonts !!
#ifdef _WIN32
const std::string FONT_PATH = "C:/Windows/Fonts/arial.ttf";
#elif __linux__
const std::string FONT_PATH = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf";
#elif __APPLE__
const std::string FONT_PATH = "/Library/Fonts/Arial Unicode.ttf";
#endif

}   // namespace cfg
