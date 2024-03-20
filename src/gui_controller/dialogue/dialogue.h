#pragma once
#include <string>
#include <vector>
#include <memory>
#include "static_data/game_config.h"
#include "renderer/graphics.h"
#include "gui_controller/timed_count.h"
#include "gui_controller/game/game_machine.h"
#include <functional>
#include <numeric>
#include <memory>

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
        virtual ~ScriptNode() {};
    };

    class QuoteNode : public ScriptNode {
    public:
        QuoteNode(std::string content, std::string sprite,  ScriptNode* next, std::function<void(gui::game::GameMachine* gm)> meta_action) :
        content(content), sprite(sprite), next(next), meta_action(meta_action) {}
        std::string content;
        std::string sprite;
        ScriptNode* next;
        std::function<void(gui::game::GameMachine* gm)> meta_action;
    };

    class ChoiceNode : public ScriptNode {
    public:
        ChoiceNode(std::vector<ScriptNode*> next_pool, std::vector<std::string> string_pool, std::function<void(gui::game::GameMachine* gm)> meta_action) :
        next_pool(next_pool), string_pool(string_pool), meta_action(meta_action) {}
        std::vector<ScriptNode*> next_pool;
        std::vector<std::string> string_pool;
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
    graphics::Color m_text_color = "#ffffff";
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
    void setEntryPoint(script::ScriptNode* entry_point, gui::game::GameMachine* gm);
    void nextQuote(gui::game::GameMachine* gm);
    void skip();
    void update(uint64_t delta_time);
    void draw(std::shared_ptr<graphics::Renderer> renderer);
    bool isActive() const;
    void handleActionKeyPressed(gui::game::GameMachine* gm); // nextQuote() or skip() call depending of text animation status
    void nextChoice();
    void prevChoice();
    void choose(gui::game::GameMachine* gm);
private:
    bool m_is_active;
    bool m_is_dialogue;
    script::ScriptNode* m_current_quote;
    DialogueWindow m_dialogue_window;
    gui::TimedCount m_character_anim;
    uint32_t m_active_choice;
    std::vector<script::ScriptNode*> m_next_steps;
    std::vector<std::string> m_choice_lines;
    void drawChoices() const;
};
}
