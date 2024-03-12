#include "dialogue.h"
#include "static_data/game_config.h"
#include "renderer/graphics.h"
#include <iostream>
#include <string>

using namespace dl;

std::vector<std::string> splitByLines(std::string str) {
    std::vector<std::string> result;
    std::string current_line = "";
    uint32_t current_characters = 0;
    std::string current_word = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            if (current_word.length() + current_characters < LINE_LENGTH) {
                current_line += current_word + ' ';
                current_characters += current_word.length();
                current_word = "";
            }
            else {
                result.push_back(current_line);
                current_line = current_word + ' ';
                current_characters = current_word.length();
                current_word = "";
            }
        }
        else if (str[i] == '\n') {
            current_line += current_word;
            result.push_back(current_line);
            current_characters = 0;
            current_word = "";
            current_line = "";
        }
        else {
            current_word.push_back(str[i]);
        }
    }
    current_line += current_word;
    result.push_back(current_line);
    return result;
}

DialogueWindow::DialogueWindow(std::string content, std::string sprite) :
    m_content(splitByLines(content)),
    m_sprite(sprite),
    m_content_len(content.length()),
    m_current_index(0),
    m_current_line(0),
    m_font_size(cfg::DIALOGUE_FONT_SIZE),
    m_font_speed(cfg::DIALOGUE_FONT_SPEED),
    m_is_finished(false),
    m_demo_sprite(std::make_shared<graphics::Sprite>("test1.png")) { }

DialogueWindow::DialogueWindow() :
        m_content(splitByLines("")),
        m_sprite(""),
        m_content_len(0),
        m_current_index(0),
        m_current_line(0),
        m_font_size(cfg::DIALOGUE_FONT_SIZE),
        m_font_speed(cfg::DIALOGUE_FONT_SPEED),
        m_is_finished(false),
        m_demo_sprite(std::make_shared<graphics::Sprite>("test1.png")) { }

void DialogueWindow::changeQuote(std::string new_content, std::string new_sprite) {
    std::cout << "123" << std::endl;
    m_content = splitByLines(new_content);
    m_sprite = new_sprite;
    m_content_len = new_content.length();
    m_current_line = 0;
    m_current_index = 0;
    m_font_size = 0;
    m_font_speed = 0;
    m_is_finished = 0;
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
    for (int i = 0; i < m_content.size(); i++) {
        renderer->drawText(
                WINDOW_MARGIN + PORTRAIT_SIZE + WINDOW_PADDING,
                cfg::WINDOW_HEIGHT - DIALOGUE_WINDOW_HEIGHT + WINDOW_MARGIN + WINDOW_PADDING + LINE_HEIGHT * i,
                m_content[i]);
    }

}
