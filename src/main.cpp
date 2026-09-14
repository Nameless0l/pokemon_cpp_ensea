#include <iostream>
#include "pokedex.hpp"
#include "game_engine.hpp"

int main()
{
    try
    {
        Pokemon::showLifeCycle = false;

        Pokedex &pokedex = Pokedex::getInstance();
        GameEngine engine(pokedex);
        engine.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
