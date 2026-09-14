#include <limits>
#include <iostream>
#include "abstract_state.hpp"

int AbstractState::askChoice(int min, int max)
{
    int choice = 0;

    while (true)
    {
        std::cout << "> ";
        if (std::cin >> choice && choice >= min && choice <= max)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }

        if (std::cin.eof())
        {
            return max;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Choix entre " << min << " et " << max << "." << std::endl;
    }
}

void AbstractState::waitForEnter()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
