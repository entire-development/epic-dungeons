#pragma once
#include <string>
#include <vector>
#include <memory>
#include "static_data/game_config.h"
#include "renderer/graphics.h"
#include "gui_controller/timed_count.h"

namespace dl {
const uint32_t DIALOGUE_WINDOW_WIDTH = cfg::WINDOW_WIDTH;
const uint32_t DIALOGUE_WINDOW_HEIGHT = cfg::WINDOW_HEIGHT / 3;
const uint32_t WINDOW_MARGIN = 32;
const uint32_t WINDOW_PADDING = 16;
const uint32_t PORTRAIT_SIZE = DIALOGUE_WINDOW_HEIGHT - WINDOW_MARGIN * 2;
const uint32_t LINE_HEIGHT = 40;    // pixels
const uint32_t LINE_LENGTH = 47;    // characters
const uint32_t CHAR_WIDTH = 18;     // pixels

std::string preprocessString(const std::string& str);

namespace script {
    struct ScriptNode {
        std::function<void(void)> meta_action;
    };

    struct QuoteNode : public ScriptNode {
        std::string content;
        std::string sprite;
        QuoteNode* next;
    };

    struct ChoiseNode : public ScriptNode {
        std::vector<ScriptNode*> next_pool;
        std::vector<std::string> string_pool;
        uint32_t timer;
    };
}

class DialogueWindow { // to draw single dialogue window
public:
    DialogueWindow();
    DialogueWindow(const std::string& content, const std::string& sprite);
    void changeQuote(const std::string& new_content, const std::string& new_sprite);
    void drawQuote(graphics::Renderer* renderer);
    void update(uint32_t current_character);
    void forceFinish();
    bool isFinished();
private:
    std::vector<std::string> m_content;
    std::string m_sprite;
    uint32_t m_current_index;
    uint32_t m_content_len;
    uint32_t m_current_line;
    uint32_t m_font_size;
    mutable int m_delay = 0;
    bool m_is_finished;
    // TODO: REFACTOR LATER
    std::shared_ptr<graphics::Sprite> m_demo_sprite;
};

class DialogueManager { // to manage dialogue branches, meta-actions etc
public:
    DialogueManager();
    explicit DialogueManager(script::QuoteNode entry_point);
    void setEntryPoint(script::QuoteNode entry_point);
    void nextQuote();
    void skip();
    void update(uint64_t delta_time, graphics::Renderer* renderer);
    bool isFinished() const;
    void handleActionKeyPressed(); // nextQuote() or skip() call depending of text animation status
private:
    bool m_is_active;
    script::QuoteNode m_current_quote;
    DialogueWindow m_dialogue_window;
    gui::TimedCount m_character_anim;
};
}
