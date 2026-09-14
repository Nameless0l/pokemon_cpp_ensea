#include "pokemon_party.hpp"

#include <stdexcept>

#include "pokemon_not_found.hpp"

void Pokemon_Party::addPokemon(const std::shared_ptr<Pokemon> &pokemon)
{
    if (pokemon == nullptr)
    {
        throw std::invalid_argument("On ne range pas un Pokémon inexistant dans l'équipe.");
    }
    pokemons.push_back(pokemon);
}

std::shared_ptr<Pokemon> Pokemon_Party::getPokemonByIndex(std::size_t index)
{
    if (index >= pokemons.size())
    {
        throw PokemonNotFound("Aucun Pokémon à l'indice " + std::to_string(index) + " dans l'équipe.");
    }

    std::shared_ptr<Pokemon> taken = pokemons.at(index);
    pokemons.erase(pokemons.begin() + static_cast<std::ptrdiff_t>(index));
    return taken;
}

std::shared_ptr<Pokemon> Pokemon_Party::getPokemonByName(const std::string &name)
{
    std::size_t index = indexOfName(name);
    if (index == pokemons.size())
    {
        throw PokemonNotFound("Aucun Pokémon nommé " + name + " dans l'équipe.");
    }
    return getPokemonByIndex(index);
}
