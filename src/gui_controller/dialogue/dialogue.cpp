#include "dialogue.h"
#include "static_data/game_config.h"
#include "renderer/graphics.h"
#include <iostream>
#include <string>

using namespace dl;

namespace METADATA {
    std::string SHORTPAUSE = "$p$p$p$p$p$p$p$p$p$p$p";
    std::string LONGPAUSE = "$p$p$p$p$p$p$p$p$p$p$p$p$p$p$p$p$p$p";
};

std::string dl::preprocessString(const std::string& str) {
    std::string result  = "";
    size_t last_index = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i - 1] == '$') continue; // preprocess ignore character.
        if (str[i] == ',') {
            result += (str.substr(last_index, i - last_index + 1) + METADATA::SHORTPAUSE);
            last_index = i + 1;
        }
        if (str[i] == '.') {
            result += (str.substr(last_index, i - last_index + 1) + METADATA::LONGPAUSE);
            last_index = i + 1;
        }
    }
    result += str.substr(last_index);
    return result;
}

std::vector<std::string> preprocessVector(const std::vector<std::string>& vec) {
    std::vector<std::string> result;
    for (std::string item : vec) {
        result.push_back(preprocessString(item));
    }
    return result;
}

std::vector<std::string> splitByLines(const std::string& str) {
    std::vector<std::string> result;
    std::string current_line = "";
    bool is_metadata = false;
    uint32_t current_characters = 0;
    std::string current_word = "";
    uint32_t current_word_len;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '$' || str[i] == '[') is_metadata = true;
        if (str[i - 1] == '$' || str[i] == ']') {
            is_metadata = false;
            current_word.push_back(str[i]);
            continue;
        }
        if (!is_metadata) {
            if (str[i] == ' ') {
                if (current_word_len + current_characters < LINE_LENGTH) {
                    current_line += current_word + ' ';
                    current_characters += current_word_len;
                    current_word = "";
                    current_word_len = 0;
                } else {
                    result.push_back(current_line);
                    current_line = current_word + ' ';
                    current_characters = current_word_len + 1;
                    current_word_len = 0;
                    current_word = "";
                }
                continue;
            }
            if (str[i] == '\n') {
                current_line += current_word;
                result.push_back(current_line);
                current_characters = 0;
                current_word = "";
                current_word_len = 0;
                current_line = "";
                continue;
            }
        }
        current_word.push_back(str[i]);
        if (!is_metadata) current_word_len++;
    }
    current_line += current_word;
    result.push_back(current_line);
    return result;
}

DialogueWindow::DialogueWindow(std::string content, std::string sprite) :
    m_content(splitByLines(preprocessString(content))),
    m_sprite(sprite),
    m_content_len(content.length()),
    m_current_index(0),
    m_current_line(0),
    m_font_size(cfg::DIALOGUE_FONT_SIZE),
    m_is_finished(false),
    m_demo_sprite(std::make_shared<graphics::Sprite>("test1.png")) { }

DialogueWindow::DialogueWindow() :
    m_content(std::vector<std::string>()),
    m_sprite(""),
    m_content_len(0),
    m_current_index(0),
    m_current_line(0),
    m_font_size(cfg::DIALOGUE_FONT_SIZE),
    m_is_finished(false),
    m_demo_sprite(std::make_shared<graphics::Sprite>("test1.png")) { }

void DialogueWindow::changeQuote(std::string new_content, std::string new_sprite) {
    std::string preprocessed_str = preprocessString(new_content);
    m_content = (splitByLines(preprocessed_str));
    m_sprite = new_sprite;
    m_content_len = preprocessed_str.length();
    m_current_line = 0;
    m_current_index = 0;
};

void DialogueWindow::finishCurrentQuote() {

}

void DialogueWindow::drawQuote(graphics::Renderer* renderer) const {
    // CONTAINER
    renderer->drawRec({
        .x = WINDOW_MARGIN, .y = cfg::WINDOW_HEIGHT - DIALOGUE_WINDOW_HEIGHT + WINDOW_MARGIN,
        .w = DIALOGUE_WINDOW_WIDTH - WINDOW_MARGIN * 2, .h = DIALOGUE_WINDOW_HEIGHT - WINDOW_MARGIN * 2,
        .color = graphics::Color("#000000"), .stroke = 5,
        .stroke_color = graphics::Color("#ffffff"),
    });

    // PORTRAIT (REFACTOR LATER)
    m_demo_sprite->toSize(PORTRAIT_SIZE, PORTRAIT_SIZE);
    m_demo_sprite->setColor({255, 255, 255, 255});
    renderer->draw(*m_demo_sprite, WINDOW_MARGIN, cfg::WINDOW_HEIGHT - DIALOGUE_WINDOW_HEIGHT + WINDOW_MARGIN);

    // TEXT
    uint32_t current_len = 0;
    uint32_t char_pos = 0;
    bool display = true;
    for (int i = 0; i < m_content.size(); i++) {
        std::string line = m_content[i];
        char_pos = 0;
        for (int j = 0; j < line.length(); j++) { // I will explain this later
            // parse metadata
            display = true;
            if (line[j] == '$' || line[j - 1] == '$') {
                display = false;
            }
            else if (line[j] == '[') { // handle metadata
                std::string property = "";
                std::string value = "";
                bool is_property = true;
                int temp_index;
                for (temp_index = j; line[temp_index] != ']'; temp_index++){
                    if (line[temp_index] == ' ') continue;
                    if (line[temp_index == '=']) {
                        is_property = false;
                        continue;
                    }
                    if (is_property) property.push_back(line[temp_index]);
                    else value.push_back(line[temp_index]);
                }
                // handle actions
                // TODO handle actions
            }
            else {
                char_pos++;
            }

            // draw character
            if (display && current_len < m_current_index) renderer->draw(graphics::Text(std::string(&line[j], &line[j + 1])),
                               WINDOW_MARGIN + PORTRAIT_SIZE + WINDOW_PADDING + char_pos * CHAR_WIDTH,
                               10 + cfg::WINDOW_HEIGHT - DIALOGUE_WINDOW_HEIGHT + WINDOW_MARGIN + WINDOW_PADDING + LINE_HEIGHT * i);
            current_len++;
        }
    }
}

void DialogueWindow::update(uint32_t current_character) {
    m_current_index = current_character;
}