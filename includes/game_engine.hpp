#pragma once

#include <memory>
#include <random>
#include "pokedex.hpp"
#include "pokemon_party.hpp"
#include "abstract_state.hpp"
#include "pokemon_attack.hpp"

class GameEngine
{
private:
    Pokedex &pokedex;
    // party est déclarée avant attack : le constructeur de attack la prend en référence.
    Pokemon_Party party;
    Pokemon_Attack attack;

    std::unique_ptr<AbstractState> currentState;
    std::unique_ptr<AbstractState> nextState;
    bool running;
    std::mt19937 randomEngine;

public:
    explicit GameEngine(Pokedex &pokedex);

    void run();
    void stop();
    void setState(std::unique_ptr<AbstractState> state);

    int random(int min, int max);
    std::shared_ptr<Pokemon> randomWildPokemon();

    Pokedex &getPokedex();
    Pokemon_Party &getParty();
    Pokemon_Attack &getAttack();
};
