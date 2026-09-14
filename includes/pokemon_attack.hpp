#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "pokemon_party.hpp"
#include "pokemon_vector.hpp"

class Pokemon_Attack : public Pokemon_Vector
{
public:
    static constexpr std::size_t MAX_SIZE = 6;

private:
    // L'équipe complète vit en dehors du groupe d'attaque : on la garde par référence.
    Pokemon_Party &party;

public:
    explicit Pokemon_Attack(Pokemon_Party &party);
    Pokemon_Attack(Pokemon_Party &party, const std::vector<std::string> &names);

    std::shared_ptr<Pokemon> getPokemonByIndex(std::size_t index) override;
    std::shared_ptr<Pokemon> getPokemonByName(const std::string &name) override;

    void addFromParty(std::size_t indexInParty);
    void giveBack(std::size_t index);
    void giveBackAll();
    void swapPositions(std::size_t first, std::size_t second);

    bool isFull() const;
    Pokemon_Party &getParty() const;
};
