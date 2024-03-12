#include "dialogue.h"
#include "static_data/game_config.h"
#include "renderer/graphics.h"
#include <iostream>
#include <string>

using namespace dl;

DialogueWindow::DialogueWindow(std::string content, std::string sprite) :
    m_content(content),
    m_sprite(sprite),
    m_content_len(content.length()),
    m_current_index(0),
    m_current_line(0),
    m_font_size(cfg::DIALOGUE_FONT_SIZE),
    m_font_speed(cfg::DIALOGUE_FONT_SPEED),
    m_is_finished(false),
    m_demo_sprite(std::make_shared<graphics::Sprite>("test1.png")) { }

void DialogueWindow::changeQuote(std::string new_content, std::string new_sprite) {
    std::cout << "123" << std::endl;
    m_content = new_content;
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
    std::cout << "test" << std::endl;
    renderer->drawRec({
        .x = WINDOW_MARGIN, .y = cfg::WINDOW_HEIGHT - DIALOGUE_WINDOW_HEIGHT + WINDOW_MARGIN,
        .w = DIALOGUE_WINDOW_WIDTH - WINDOW_MARGIN * 2, .h = DIALOGUE_WINDOW_HEIGHT - WINDOW_MARGIN * 2,
        .color = graphics::Color("#000000"), .stroke = 5,
        .stroke_color = graphics::Color("#ffffff"),
    });

    // REFACTOR LATER
    m_demo_sprite->toSize(PORTRAIT_SIZE, PORTRAIT_SIZE);
    m_demo_sprite->setColor({255, 255, 255, 255});
    renderer->draw(*m_demo_sprite, WINDOW_MARGIN, cfg::WINDOW_HEIGHT - DIALOGUE_WINDOW_HEIGHT + WINDOW_MARGIN);
}