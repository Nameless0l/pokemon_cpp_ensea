#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "pokedex.hpp"
#include "pokemon_not_found.hpp"

// #,Name,Type 1,Type 2,Total,HP,Attack,Defense,Sp. Atk,Sp. Def,Speed,Generation,Legendary
static const std::size_t COLUMN_ID = 0;
static const std::size_t COLUMN_NAME = 1;
static const std::size_t COLUMN_HP = 5;
static const std::size_t COLUMN_ATTACK = 6;
static const std::size_t COLUMN_DEFENSE = 7;
static const std::size_t COLUMN_GENERATION = 11;
static const std::size_t COLUMN_COUNT = 13;

static std::vector<std::string> splitLine(const std::string &line, char separator)
{
    std::vector<std::string> cells;
    std::stringstream stream(line);
    std::string cell;

    while (std::getline(stream, cell, separator))
    {
        cells.push_back(cell);
    }
    return cells;
}

Pokedex::Pokedex(const std::string &csvFileName)
{
    loadFromCsv(csvFileName);
}

void Pokedex::loadFromCsv(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier " + fileName);
    }

    std::string line;
    std::size_t lineNumber = 0;

    while (std::getline(file, line))
    {
        lineNumber++;
        if (lineNumber == 1 || line.empty())
        {
            continue;
        }

        std::vector<std::string> cells = splitLine(line, ',');
        if (cells.size() < COLUMN_COUNT)
        {
            std::cerr << "Ligne " << lineNumber << " ignorée : colonnes manquantes." << std::endl;
            continue;
        }

        pokemons.push_back(std::make_shared<Pokemon>(std::stoi(cells.at(COLUMN_ID)),
                                                     cells.at(COLUMN_NAME),
                                                     std::stod(cells.at(COLUMN_HP)),
                                                     std::stod(cells.at(COLUMN_ATTACK)),
                                                     std::stod(cells.at(COLUMN_DEFENSE)),
                                                     std::stoi(cells.at(COLUMN_GENERATION))));
    }
}

Pokedex &Pokedex::getInstance(const std::string &csvFileName)
{
    static Pokedex instance(csvFileName);
    return instance;
}

std::shared_ptr<Pokemon> Pokedex::getPokemonByIndex(std::size_t index)
{
    if (index >= pokemons.size())
    {
        throw PokemonNotFound("Aucun Pokémon à l'indice " + std::to_string(index) + " dans le Pokédex.");
    }
    return pokemons.at(index)->clone();
}

std::shared_ptr<Pokemon> Pokedex::getPokemonByName(const std::string &name)
{
    std::size_t index = indexOfName(name);
    if (index == pokemons.size())
    {
        throw PokemonNotFound("Aucun Pokémon nommé " + name + " dans le Pokédex.");
    }
    return pokemons.at(index)->clone();
}

std::shared_ptr<Pokemon> Pokedex::peek(std::size_t index) const
{
    return Pokemon_Vector::peek(index)->clone();
}

