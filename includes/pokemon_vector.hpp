#pragma once
#include <vector>
#include <memory>
#include <string>
#include <cstddef>
#include <functional>
#include "pokemon.hpp"

class Pokemon_Vector
{
protected:
    std::vector<std::shared_ptr<Pokemon>> pokemons;
    std::size_t indexOfName(const std::string &name) const;

public:
    using iterator = std::vector<std::shared_ptr<Pokemon>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Pokemon>>::const_iterator;

    virtual ~Pokemon_Vector() = default;

    virtual std::shared_ptr<Pokemon> getPokemonByIndex(std::size_t index) = 0;
    virtual std::shared_ptr<Pokemon> getPokemonByName(const std::string &name) = 0;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    virtual std::shared_ptr<Pokemon> peek(std::size_t index) const;
    std::size_t size() const;
    bool empty() const;
    bool contains(const std::string &name) const;
    void displayList() const;

    std::size_t countIf(const std::function<bool(const Pokemon &)> &predicate) const;
    std::vector<std::shared_ptr<Pokemon>> filter(const std::function<bool(const Pokemon &)> &predicate) const;
    void sortBy(const std::function<bool(const Pokemon &, const Pokemon &)> &comparator);
};
