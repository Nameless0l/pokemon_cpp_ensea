#include <iostream>
#include <stdexcept>
#include "pokemon.hpp"

const double Pokemon::MIN_DAMAGE = 1.0;

int Pokemon::instanceCount = 0;
bool Pokemon::showLifeCycle = true;

Pokemon::Pokemon(int id, std::string name, double maxHitPoint, double attack,
                 double defense, int generation, int evolution)
    : id(id), name(name), evolution(evolution), maxHitPoint(maxHitPoint),
      currentHitPoint(maxHitPoint), attack(attack), defense(defense), generation(generation)
{
    checkAttributes();
    instanceCount++;
    if (showLifeCycle)
    {
        std::cout << "Création de " << this->name << std::endl;
    }
}

Pokemon::Pokemon(const Pokemon &other)
    : id(other.id), name(other.name), evolution(other.evolution),
      maxHitPoint(other.maxHitPoint), currentHitPoint(other.currentHitPoint),
      attack(other.attack), defense(other.defense), generation(other.generation)
{
    instanceCount++;
    if (showLifeCycle)
    {
        std::cout << "Recopie de " << name << std::endl;
    }
}

Pokemon::~Pokemon()
{
    instanceCount--;
    if (showLifeCycle)
    {
        std::cout << "Destruction de " << name << std::endl;
    }
}

std::unique_ptr<Pokemon> Pokemon::clone() const
{
    return std::make_unique<Pokemon>(*this);
}

void Pokemon::checkAttributes() const
{
    if (id <= 0)
    {
        throw std::invalid_argument("L'identifiant doit être strictement positif.");
    }
    if (name.empty())
    {
        throw std::invalid_argument("Le nom ne peut pas être vide.");
    }
    if (evolution < 0)
    {
        throw std::invalid_argument("Le numéro d'évolution ne peut pas être négatif.");
    }
    if (evolution == id)
    {
        throw std::invalid_argument("Un Pokémon ne peut pas évoluer en lui-même.");
    }
    if (maxHitPoint <= 0.0)
    {
        throw std::invalid_argument("Les points de vie maximum doivent être strictement positifs.");
    }
    if (currentHitPoint < 0.0 || currentHitPoint > maxHitPoint)
    {
        throw std::invalid_argument("Les points de vie actuels sortent de l'intervalle [0, max].");
    }
    if (attack < 0.0)
    {
        throw std::invalid_argument("L'attaque ne peut pas être négative.");
    }
    if (defense < 0.0)
    {
        throw std::invalid_argument("La défense ne peut pas être négative.");
    }
    if (generation < 1)
    {
        throw std::invalid_argument("La génération doit valoir au moins 1.");
    }
}

int Pokemon::getId() const { return id; }
const std::string &Pokemon::getName() const { return name; }
int Pokemon::getEvolution() const { return evolution; }
double Pokemon::getMaxHitPoint() const { return maxHitPoint; }
double Pokemon::getCurrentHitPoint() const { return currentHitPoint; }
double Pokemon::getAttack() const { return attack; }
double Pokemon::getDefense() const { return defense; }
int Pokemon::getGeneration() const { return generation; }

void Pokemon::setName(std::string name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Le nom ne peut pas être vide.");
    }
    this->name = name;
}

void Pokemon::setEvolution(int evolution)
{
    if (evolution < 0)
    {
        throw std::invalid_argument("Le numéro d'évolution ne peut pas être négatif.");
    }
    if (evolution == id)
    {
        throw std::invalid_argument("Un Pokémon ne peut pas évoluer en lui-même.");
    }
    this->evolution = evolution;
}

void Pokemon::setCurrentHitPoint(double currentHitPoint)
{
    if (currentHitPoint < 0.0 || currentHitPoint > maxHitPoint)
    {
        throw std::invalid_argument("Les points de vie actuels sortent de l'intervalle [0, max].");
    }
    this->currentHitPoint = currentHitPoint;
}

bool Pokemon::isKO() const { return currentHitPoint <= 0.0; }

bool Pokemon::canEvolve() const { return evolution != 0; }

double Pokemon::hitPointRatio() const { return currentHitPoint / maxHitPoint; }

void Pokemon::heal() { currentHitPoint = maxHitPoint; }

void Pokemon::takeDamage(double damage)
{
    if (damage < 0.0)
    {
        throw std::invalid_argument("Des dégâts ne peuvent pas être négatifs.");
    }
    currentHitPoint = (damage >= currentHitPoint) ? 0.0 : currentHitPoint - damage;
}

double Pokemon::attackPokemon(Pokemon &target)
{
    if (this == &target)
    {
        std::cout << name << " ne peut pas s'attaquer lui-même." << std::endl;
        return 0.0;
    }
    if (isKO())
    {
        std::cout << name << " est KO : il ne peut plus attaquer." << std::endl;
        return 0.0;
    }
    if (target.isKO())
    {
        std::cout << target.name << " est déjà KO : l'attaque n'a aucun effet." << std::endl;
        return 0.0;
    }

    double damage = attack - target.defense / 2.0;
    if (damage < MIN_DAMAGE)
    {
        damage = MIN_DAMAGE;
    }

    target.takeDamage(damage);

    std::cout << name << " attaque " << target.name << " ! " << target.name << " perd "
              << damage << " points de vie, il lui en reste " << target.currentHitPoint
              << "." << std::endl;

    if (target.isKO())
    {
        std::cout << target.name << " est KO !" << std::endl;
    }
    return damage;
}

void Pokemon::displayInfo() const
{
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Numéro        : " << id << std::endl;
    std::cout << "Nom           : " << name << std::endl;
    std::cout << "Évolution     : " << (canEvolve() ? std::to_string(evolution) : "aucune") << std::endl;
    std::cout << "Points de vie : " << currentHitPoint << " / " << maxHitPoint << std::endl;
    std::cout << "Attaque       : " << attack << std::endl;
    std::cout << "Défense       : " << defense << std::endl;
    std::cout << "Génération    : " << generation << std::endl;
}

int Pokemon::getInstanceCount() { return instanceCount; }
