#pragma once
#include <string>
#include "events/event.h"

class Dialogue : public Action
{
public:
    Dialogue(const std::string& text, const std::string& speaker);
    Dialogue(const std::string& text, const std::string& speaker, const std::vector<std::string>& choices);

    void execute();
    void add_choice(const std::string& choice);
    
    int get_choice() const; // returns the index of the choice selected

private:
    std::string _text;
    std::string _speaker;
    std::vector<std::string> _choices;
    int _choice;
};