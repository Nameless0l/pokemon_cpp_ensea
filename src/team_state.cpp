#include <iostream>
#include "team_state.hpp"
#include "game_engine.hpp"
#include "selection_screen.hpp"
#include "exploration_state.hpp"

std::string TeamState::name() const { return "Préparation du groupe d'attaque"; }

void TeamState::run()
{
    std::cout << std::endl << "Ouverture de l'écran de sélection..." << std::endl;

    SelectionScreen screen(engine.getAttack());
    screen.run();

    std::cout << "Groupe d'attaque (" << engine.getAttack().size() << ") :" << std::endl;
    engine.getAttack().displayList();

    engine.setState(std::make_unique<ExplorationState>(engine));
}
