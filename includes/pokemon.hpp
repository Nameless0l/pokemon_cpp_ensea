#pragma once

#include <memory>
#include <string>

class Pokemon
{
private:
    int id;
    std::string name;
    // Numéro du Pokémon obtenu par évolution, 0 quand il n'en a pas.
    int evolution;
    double maxHitPoint;
    double currentHitPoint;
    double attack;
    double defense;
    int generation;

    static int instanceCount;

    void checkAttributes() const;

public:
    static const double MIN_DAMAGE;
    static bool showLifeCycle;

    ~Pokemon();
    Pokemon() = delete;
    Pokemon(const Pokemon &other);
    Pokemon(int id, std::string name, double maxHitPoint, double attack,
            double defense, int generation, int evolution = 0);

    std::unique_ptr<Pokemon> clone() const;

    int getId() const;
    double getAttack() const;
    int getEvolution() const;
    double getDefense() const;
    int getGeneration() const;
    double getMaxHitPoint() const;
    double getCurrentHitPoint() const;
    const std::string &getName() const;

    void setName(std::string name);
    void setEvolution(int evolution);
    void setCurrentHitPoint(double currentHitPoint);

    bool isKO() const;
    bool canEvolve() const;
    double hitPointRatio() const;

    void heal();
    void takeDamage(double damage);
    double attackPokemon(Pokemon &target);

    void displayInfo() const;

    static int getInstanceCount();
};
