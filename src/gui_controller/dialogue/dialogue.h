#pragma once
#include <string>
#include <vector>
#include "static_data/game_config.h"
#include "renderer/graphics.h"

namespace dl {
const uint32_t DIALOGUE_WINDOW_WIDTH = cfg::WINDOW_WIDTH;
const uint32_t DIALOGUE_WINDOW_HEIGHT = cfg::WINDOW_HEIGHT / 3;
const uint32_t WINDOW_MARGIN = 32;
const uint32_t WINDOW_PADDING = 16;
const uint32_t PORTRAIT_SIZE = DIALOGUE_WINDOW_HEIGHT - WINDOW_MARGIN * 2;
const uint32_t LINE_HEIGHT = 40; // pixels
const uint32_t LINE_LENGTH = 78; // characters

class DialogueManager { // to manage dialogue branches, meta-actions etc

};

class DialogueWindow { // to draw single dialogue window
public:
    DialogueWindow();
    DialogueWindow(std::string content, std::string sprite);
    void changeQuote(std::string new_content, std::string new_sprite);
    void finishCurrentQuote();
    void drawQuote(graphics::Renderer* renderer) const;
private:
    std::vector<std::string> m_content;
    std::string m_sprite;
    uint32_t m_current_index;
    uint32_t m_content_len;
    uint32_t m_current_line;
    uint32_t m_font_speed;
    uint32_t m_font_size;
    bool m_is_finished;

    // TODO: REFACTOR LATER
    std::shared_ptr<graphics::Sprite> m_demo_sprite;
    };
}
