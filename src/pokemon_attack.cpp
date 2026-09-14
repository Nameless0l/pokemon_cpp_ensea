#include "pokemon_attack.hpp"

#include <stdexcept>

#include "pokemon_not_found.hpp"

Pokemon_Attack::Pokemon_Attack(Pokemon_Party &party) : party(party) {}

Pokemon_Attack::Pokemon_Attack(Pokemon_Party &party, const std::vector<std::string> &names)
    : party(party)
{
    if (names.size() > MAX_SIZE)
    {
        throw std::length_error("Un groupe d'attaque compte au plus 6 Pokémon.");
    }

    // On vérifie tous les noms avant d'en sortir un seul, sinon un nom erroné
    // laisserait l'équipe à moitié vidée.
    for (const std::string &name : names)
    {
        if (!party.contains(name))
        {
            throw PokemonNotFound(name + " n'est pas dans l'équipe.");
        }
    }

    for (const std::string &name : names)
    {
        pokemons.push_back(party.getPokemonByName(name));
    }
}

std::shared_ptr<Pokemon> Pokemon_Attack::getPokemonByIndex(std::size_t index)
{
    if (index >= pokemons.size())
    {
        throw PokemonNotFound("Aucun Pokémon à l'indice " + std::to_string(index) +
                              " dans le groupe d'attaque.");
    }

    std::shared_ptr<Pokemon> taken = pokemons.at(index);
    pokemons.erase(pokemons.begin() + static_cast<std::ptrdiff_t>(index));
    return taken;
}

std::shared_ptr<Pokemon> Pokemon_Attack::getPokemonByName(const std::string &name)
{
    std::size_t index = indexOfName(name);
    if (index == pokemons.size())
    {
        throw PokemonNotFound("Aucun Pokémon nommé " + name + " dans le groupe d'attaque.");
    }
    return getPokemonByIndex(index);
}

void Pokemon_Attack::addFromParty(std::size_t indexInParty)
{
    if (isFull())
    {
        throw std::length_error("Le groupe d'attaque est déjà complet.");
    }
    pokemons.push_back(party.getPokemonByIndex(indexInParty));
}

void Pokemon_Attack::giveBack(std::size_t index)
{
    party.addPokemon(getPokemonByIndex(index));
}

void Pokemon_Attack::giveBackAll()
{
    while (!pokemons.empty())
    {
        giveBack(pokemons.size() - 1);
    }
}

void Pokemon_Attack::swapPositions(std::size_t first, std::size_t second)
{
    if (first >= pokemons.size() || second >= pokemons.size())
    {
        throw PokemonNotFound("Position hors du groupe d'attaque.");
    }
    std::swap(pokemons.at(first), pokemons.at(second));
}

bool Pokemon_Attack::isFull() const { return pokemons.size() >= MAX_SIZE; }

Pokemon_Party &Pokemon_Attack::getParty() const { return party; }
