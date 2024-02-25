#include "dialogue.h"
#include <iostream>
#include <string>
#include <utils/utils.h>

Dialogue::Dialogue(const std::string &speaker, const std::string &text) : Action(),
                                                                          _text(text),
                                                                          _speaker(speaker) {}

Dialogue::Dialogue(
    const std::string &speaker,
    const std::string &text,
    const std::vector<std::string> &choices) : Action(),
                                               _text(text),
                                               _speaker(speaker),
                                               _choices(choices) {}

void Dialogue::add_choice(const std::string &choice) { _choices.push_back(choice); }

void Dialogue::execute()
{
    std::cout << _speaker << ": " << _text << std::endl;
    if (_choices.size() > 0)
    {
        for (int i = 0; i < _choices.size(); i++)
        {
            std::cout << i + 1 << ". " << _choices[i] << std::endl;
        }
        std::cout << "Enter the number of your choice: ";
        std::string input;
        while (true)
        {
            std::cin >> input;
            if (is_number(input))
            {
                _choice = std::stoi(input) - 1;
                if (_choice >= 0 && _choice < _choices.size())
                    break;
            }
            std::cout << "Invalid choice. Please enter a number between 1 and " << _choices.size() << ": ";
        }
    }
}

int Dialogue::get_choice() const { return _choice; }