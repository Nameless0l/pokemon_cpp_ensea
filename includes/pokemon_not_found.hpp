#pragma once

#include <stdexcept>
#include <string>

// Exception dédiée, pour que l'appelant puisse rattraper ce cas précis sans intercepter toutes les autres erreurs.
class PokemonNotFound : public std::runtime_error
{
public:
    explicit PokemonNotFound(const std::string &message) : std::runtime_error(message) {}
};
