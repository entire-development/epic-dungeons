#pragma once
#include <string>
#include <vector>
#include <memory>
#include "static_data/game_config.h"
#include "renderer/graphics.h"
#include "gui_controller/timed_count.h"
#include "gui_controller/game/game_machine.h"

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
    struct ScriptNode { };

    struct QuoteNode : ScriptNode {
        std::string content;
        std::string sprite;
        QuoteNode* next;
        std::function<void(gui::game::GameMachine* gm)> meta_action;
    };

    struct ChoiseNode : ScriptNode {
        std::vector<ScriptNode*> next_pool;
        std::vector<std::string> string_pool;
        uint32_t timer;
        std::function<void(gui::game::GameMachine* gm)> meta_action;
    };
}

class DialogueWindow { // to draw single dialogue window
public:
    DialogueWindow();
    DialogueWindow(const std::string& content, const std::string& sprite);
    void changeQuote(const std::string& new_content, const std::string& new_sprite);
    void drawQuote(std::shared_ptr<graphics::Renderer> renderer);
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
    explicit DialogueManager(script::QuoteNode* entry_point);
    void setEntryPoint(script::QuoteNode* entry_point, gui::game::GameMachine* gm);
    void nextQuote(gui::game::GameMachine* gm);
    void skip();
    void update(uint64_t delta_time);
    void draw(std::shared_ptr<graphics::Renderer> renderer);
    bool isActive() const;
    void handleActionKeyPressed(); // nextQuote() or skip() call depending of text animation status
private:
    bool m_is_active;
    script::QuoteNode* m_current_quote;
    DialogueWindow m_dialogue_window;
    gui::TimedCount m_character_anim;
};
}
