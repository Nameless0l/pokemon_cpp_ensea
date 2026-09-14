#include <iostream>
#include "game_engine.hpp"
#include "encounter_state.hpp"
#include "exploration_state.hpp"

std::string EncounterState::name() const { return "Rencontre / Capture"; }

void EncounterState::run()
{
    std::shared_ptr<Pokemon> wild = engine.randomWildPokemon();

    std::cout << std::endl << "--- Rencontre ---" << std::endl;
    std::cout << "Un " << wild->getName() << " sauvage apparaît !" << std::endl;
    std::cout << "1. Lancer une Pokéball" << std::endl;
    std::cout << "2. Fuir" << std::endl;

    if (askChoice(1, 2) == 1)
    {
        if (engine.random(1, 100) <= 50)
        {
            std::cout << wild->getName() << " est capturé !" << std::endl;
            engine.getParty().addPokemon(wild);
        }
        else
        {
            std::cout << wild->getName() << " s'est échappé." << std::endl;
        }
    }
    else
    {
        std::cout << "Vous prenez la fuite." << std::endl;
    }

    engine.setState(std::make_unique<ExplorationState>(engine));
}
