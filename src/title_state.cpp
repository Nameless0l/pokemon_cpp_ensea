#include <iostream>
#include "game_engine.hpp"
#include "title_state.hpp"
#include "exploration_state.hpp"

std::string TitleState::name() const { return "Écran d'accueil"; }

void TitleState::run()
{
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "            P O K É M O N               " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Appuyez sur Entrée pour partir à l'aventure." << std::endl;

    waitForEnter();

    engine.setState(std::make_unique<ExplorationState>(engine));
}
