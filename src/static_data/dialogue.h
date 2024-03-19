#include "gui_controller/dialogue/dialogue.h"
#include "gui_controller/game/game_machine.h"

using namespace dl;

dl::script::QuoteNode quote_3 = {
        .content = "Quote 3!",
        .sprite = "123",
        .next = nullptr,
        .meta_action = [](gui::game::GameMachine* gm) {
            std::cout << "Quote 3 meta action!";
        }
};

dl::script::QuoteNode quote_2 = {
        .content = "Quote 2!",
        .sprite = "123",
        .next = &quote_3,
        .meta_action = [](gui::game::GameMachine* gm) {
            std::cout << "Quote 2 meta action!";
        }
};

dl::script::QuoteNode quote_1 = {
        .content = "Quote 1!",
        .sprite = "123",
        .next = &quote_2,
        .meta_action = [](gui::game::GameMachine* gm) {
            std::cout << "Quote 1 meta action!";
        }
};