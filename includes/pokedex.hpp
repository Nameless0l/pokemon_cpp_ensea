#pragma once

#include <string>
#include "pokemon_vector.hpp"

class Pokedex : public Pokemon_Vector
{
private:
    explicit Pokedex(const std::string &csvFileName);

    void loadFromCsv(const std::string &fileName);

public:
    Pokedex(const Pokedex &other) = delete;
    Pokedex &operator=(const Pokedex &other) = delete;

    static Pokedex &getInstance(const std::string &csvFileName = "data/pokedex.csv");

    std::shared_ptr<Pokemon> peek(std::size_t index) const override;
    std::shared_ptr<Pokemon> getPokemonByIndex(std::size_t index) override;
    std::shared_ptr<Pokemon> getPokemonByName(const std::string &name) override;
};
