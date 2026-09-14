#include <iostream>
#include "game_engine.hpp"
#include "title_state.hpp"
#include "game_over_state.hpp"

std::string GameOverState::name() const { return "Game Over"; }

void GameOverState::run()
{
    std::cout << std::endl << "--- GAME OVER ---" << std::endl;
    std::cout << "1. Soigner l'équipe et recommencer" << std::endl;
    std::cout << "2. Quitter" << std::endl;

    if (askChoice(1, 2) == 1)
    {
        for (const std::shared_ptr<Pokemon> &pokemon : engine.getParty())
        {
            pokemon->heal();
        }
        engine.setState(std::make_unique<TitleState>(engine));
    }
    else
    {
        engine.stop();
    }
}
