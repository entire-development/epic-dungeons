#pragma once
#include "gui_controller/dialogue/dialogue.h"
#include "gui_controller/game/game_machine.h"

using namespace gui;

dl::script::QuoteNode choice_1 = dl::script::QuoteNode(
        "Choice 1! Wise choice.",
        "123",
        nullptr,
        [](gui::game::GameMachine* gm) {
            std::cout << "Choice 1 meta action!";
        });

dl::script::QuoteNode choice_2 = dl::script::QuoteNode(
        "Choice 2! Wise choice.",
        "123",
        nullptr,
        [](gui::game::GameMachine* gm) {
            std::cout << "Choice 2 meta action!";
        });

dl::script::QuoteNode choice_3 = dl::script::QuoteNode(
        "Choice 3! Wise choice.",
        "123",
        nullptr,
        [](gui::game::GameMachine* gm) {
            std::cout << "Choice 3 meta action!";
        });

dl::script::ChoiceNode choice_node = dl::script::ChoiceNode(
        {&choice_1, &choice_2, &choice_3},
        {"Choose 1", "Choose 2", "Choose 3"},
        [](gui::game::GameMachine* gm) {
            std::cout << "Choose!" << std::endl;
        });

dl::script::QuoteNode quote_3 = dl::script::QuoteNode(
        "[size=30]Quote 3! Check. Out. These. Delays![/size]",
        "123",
        &choice_node,
        [](gui::game::GameMachine* gm) {
            std::cout << "Quote 3 meta action!";
        });

dl::script::QuoteNode quote_2 = dl::script::QuoteNode(
        "[color=#ff6666]gay [color=#eb8f34] gay [color=#eb8f34] ho [color=#e6cd15]mo [color=#30e314]sex [color=#10e3dc]ual [color=#de10d4] gay[/color]",
        "123",
        &quote_3,
        [](gui::game::GameMachine* gm) {
            std::cout << "Quote 2 meta action!";
        });

dl::script::QuoteNode quote_1 = dl::script::QuoteNode(
        "Quote 1! This is quote test. [color=#6666ff] BLUE TEXT!!!! [/color]",
        "123",
        &quote_2,
        [](gui::game::GameMachine* gm) {
            std::cout << "Quote 1 meta action!";
        });
