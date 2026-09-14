#include <iomanip>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "pokemon_vector.hpp"
#include "pokemon_not_found.hpp"

std::size_t Pokemon_Vector::indexOfName(const std::string &name) const
{
    const_iterator found = std::find_if(pokemons.begin(), pokemons.end(),
                                        [&name](const std::shared_ptr<Pokemon> &pokemon)
                                        { return pokemon->getName() == name; });

    return static_cast<std::size_t>(std::distance(pokemons.begin(), found));
}

Pokemon_Vector::iterator Pokemon_Vector::begin() { return pokemons.begin(); }

Pokemon_Vector::iterator Pokemon_Vector::end() { return pokemons.end(); }

Pokemon_Vector::const_iterator Pokemon_Vector::begin() const { return pokemons.begin(); }

Pokemon_Vector::const_iterator Pokemon_Vector::end() const { return pokemons.end(); }

std::shared_ptr<Pokemon> Pokemon_Vector::peek(std::size_t index) const
{
    if (index >= pokemons.size())
    {
        throw PokemonNotFound("Aucun Pokémon à l'indice " + std::to_string(index) + ".");
    }
    return pokemons.at(index);
}

std::size_t Pokemon_Vector::size() const { return pokemons.size(); }

bool Pokemon_Vector::empty() const { return pokemons.empty(); }

bool Pokemon_Vector::contains(const std::string &name) const
{
    return indexOfName(name) != pokemons.size();
}

void Pokemon_Vector::displayList() const
{
    std::cout << std::setw(8) << std::left << "Indice" << "Nom" << std::endl;
    std::cout << "------------------------------" << std::endl;

    if (pokemons.empty())
    {
        std::cout << "(ensemble vide)" << std::endl;
        return;
    }

    std::size_t index = 0;
    for (const std::shared_ptr<Pokemon> &pokemon : *this)
    {
        std::cout << std::setw(8) << std::left << index << pokemon->getName() << std::endl;
        index++;
    }
}

std::size_t Pokemon_Vector::countIf(const std::function<bool(const Pokemon &)> &predicate) const
{
    return static_cast<std::size_t>(
        std::count_if(pokemons.begin(), pokemons.end(),
                      [&predicate](const std::shared_ptr<Pokemon> &pokemon)
                      { return predicate(*pokemon); }));
}

std::vector<std::shared_ptr<Pokemon>> Pokemon_Vector::filter(
    const std::function<bool(const Pokemon &)> &predicate) const
{
    std::vector<std::shared_ptr<Pokemon>> selection;

    std::copy_if(pokemons.begin(), pokemons.end(), std::back_inserter(selection),
                 [&predicate](const std::shared_ptr<Pokemon> &pokemon)
                 { return predicate(*pokemon); });

    return selection;
}

void Pokemon_Vector::sortBy(const std::function<bool(const Pokemon &, const Pokemon &)> &comparator)
{
    std::sort(pokemons.begin(), pokemons.end(),
              [&comparator](const std::shared_ptr<Pokemon> &left,
                            const std::shared_ptr<Pokemon> &right)
              { return comparator(*left, *right); });
}
// lambda
