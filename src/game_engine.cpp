#include "game_engine.hpp"
#include "title_state.hpp"

GameEngine::GameEngine(Pokedex &pokedex)
    : pokedex(pokedex), attack(party), running(false), randomEngine(std::random_device{}())
{
    party.addPokemon(pokedex.getPokemonByName("Bulbasaur"));
    party.addPokemon(pokedex.getPokemonByName("Charmander"));
    party.addPokemon(pokedex.getPokemonByName("Squirtle"));

    currentState = std::make_unique<TitleState>(*this);
}

void GameEngine::setState(std::unique_ptr<AbstractState> state)
{
    // On ne remplace pas l'état courant tout de suite : il est en train de
    // s'exécuter, le détruire maintenant ferait disparaître le this de run().
    nextState = std::move(state);
}

void GameEngine::run()
{
    running = true;

    while (running)
    {
        currentState->run();

        if (nextState != nullptr)
        {
            currentState = std::move(nextState);
        }
    }
}

void GameEngine::stop() { running = false; }

int GameEngine::random(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(randomEngine);
}

std::shared_ptr<Pokemon> GameEngine::randomWildPokemon()
{
    return pokedex.getPokemonByIndex(static_cast<std::size_t>(random(0, static_cast<int>(pokedex.size()) - 1)));
}

Pokedex &GameEngine::getPokedex() { return pokedex; }
Pokemon_Party &GameEngine::getParty() { return party; }
Pokemon_Attack &GameEngine::getAttack() { return attack; }
