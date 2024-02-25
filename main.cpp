#include <iostream>

#include "events/actions/dialogue/dialogue.h"
#include "events/event.h"

int main() {
    std::vector<std::string> choices = {"Yes", "No"};

    Dialogue d("John", "Hello, World!", choices);
    d.execute();

    int choice = d.get_choice();
    printf("Choice: %s\n", choices[choice].c_str());
    
    return 0;
}