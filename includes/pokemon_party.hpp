#pragma once

#include "pokemon_vector.hpp"

class Pokemon_Party : public Pokemon_Vector
{
public:
    Pokemon_Party() = default;

    void addPokemon(const std::shared_ptr<Pokemon> &pokemon);

    std::shared_ptr<Pokemon> getPokemonByIndex(std::size_t index) override;
    std::shared_ptr<Pokemon> getPokemonByName(const std::string &name) override;
};
