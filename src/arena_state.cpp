#include <iostream>
#include "arena_state.hpp"
#include "game_engine.hpp"
#include "game_over_state.hpp"
#include "exploration_state.hpp"

std::string ArenaState::name() const { return "Combat dans l'arène"; }

void ArenaState::run()
{
    Pokemon_Party &party = engine.getParty();

    std::shared_ptr<Pokemon> fighter = nullptr;
    for (const std::shared_ptr<Pokemon> &pokemon : party)
    {
        if (!pokemon->isKO())
        {
            fighter = pokemon;
            break;
        }
    }

    if (fighter == nullptr)
    {
        std::cout << "Aucun Pokémon en état de combattre." << std::endl;
        engine.setState(std::make_unique<GameOverState>(engine));
        return;
    }

    std::shared_ptr<Pokemon> opponent = engine.randomWildPokemon();

    std::cout << std::endl << "--- Arène ---" << std::endl;
    std::cout << "Le champion envoie " << opponent->getName() << " !" << std::endl;
    std::cout << fighter->getName() << " entre sur le terrain." << std::endl;

    while (!fighter->isKO() && !opponent->isKO())
    {
        std::cout << std::endl;
        std::cout << fighter->getName() << " " << fighter->getCurrentHitPoint() << " PV  |  "
                  << opponent->getName() << " " << opponent->getCurrentHitPoint() << " PV" << std::endl;
        std::cout << "1. Attaquer" << std::endl;
        std::cout << "2. Abandonner le combat" << std::endl;

        if (askChoice(1, 2) == 2)
        {
            std::cout << "Vous quittez l'arène." << std::endl;
            engine.setState(std::make_unique<ExplorationState>(engine));
            return;
        }

        fighter->attackPokemon(*opponent);

        if (!opponent->isKO())
        {
            opponent->attackPokemon(*fighter);
        }
    }

    if (opponent->isKO())
    {
        std::cout << "Victoire ! Vous repartez avec " << opponent->getName() << "." << std::endl;
        opponent->heal();
        party.addPokemon(opponent);
        engine.setState(std::make_unique<ExplorationState>(engine));
    }
    else
    {
        std::cout << fighter->getName() << " est KO." << std::endl;
        engine.setState(std::make_unique<GameOverState>(engine));
    }
}
