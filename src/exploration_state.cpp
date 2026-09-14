#include <iostream>
#include "arena_state.hpp"
#include "game_engine.hpp"
#include "encounter_state.hpp"
#include "exploration_state.hpp"

std::string ExplorationState::name() const { return "Exploration"; }

void ExplorationState::run()
{
    std::cout << std::endl << "--- Exploration ---" << std::endl;
    std::cout << "1. Marcher dans les hautes herbes" << std::endl;
    std::cout << "2. Voir mon équipe" << std::endl;
    std::cout << "3. Quitter" << std::endl;

    int choice = askChoice(1, 3);

    if (choice == 2)
    {
        engine.getParty().displayList();
        return;
    }
    if (choice == 3)
    {
        std::cout << "À bientôt !" << std::endl;
        engine.stop();
        return;
    }

    int roll = engine.random(1, 100);

    if (roll <= 45)
    {
        engine.setState(std::make_unique<EncounterState>(engine));
    }
    else if (roll <= 75)
    {
        engine.setState(std::make_unique<ArenaState>(engine));
    }
    else
    {
        std::cout << "Les herbes sont calmes." << std::endl;
    }
}
