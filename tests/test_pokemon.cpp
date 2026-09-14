#include <iostream>
#include <memory>
#include <stdexcept>

#include "pokemon.hpp"
#include "test_utils.hpp"

static void test_le_constructeur_initialise_les_attributs()
{
    std::cerr << "test_le_constructeur_initialise_les_attributs" << std::endl;

    Pokemon p(25, "Pikachu", 35.0, 55.0, 40.0, 1, 26);

    CHECK(p.getId() == 25);
    CHECK(p.getName() == "Pikachu");
    CHECK(p.getEvolution() == 26);
    CHECK_NEAR(p.getMaxHitPoint(), 35.0);
    CHECK_NEAR(p.getAttack(), 55.0);
    CHECK_NEAR(p.getDefense(), 40.0);
    CHECK(p.getGeneration() == 1);
}

static void test_les_points_de_vie_demarrent_au_maximum()
{
    std::cerr << "test_les_points_de_vie_demarrent_au_maximum" << std::endl;

    Pokemon p(25, "Pikachu", 35.0, 55.0, 40.0, 1);

    CHECK_NEAR(p.getCurrentHitPoint(), p.getMaxHitPoint());
    CHECK_NEAR(p.hitPointRatio(), 1.0);
    CHECK(!p.isKO());
}

static void test_l_evolution_vaut_zero_par_defaut()
{
    std::cerr << "test_l_evolution_vaut_zero_par_defaut" << std::endl;

    Pokemon p(25, "Pikachu", 35.0, 55.0, 40.0, 1);

    CHECK(p.getEvolution() == 0);
    CHECK(!p.canEvolve());
}

static void test_le_constructeur_de_recopie_copie_les_attributs()
{
    std::cerr << "test_le_constructeur_de_recopie_copie_les_attributs" << std::endl;

    Pokemon original(6, "Dracofeu", 78.0, 84.0, 78.0, 1);
    original.takeDamage(20.0);

    Pokemon copie(original);

    CHECK(copie.getName() == original.getName());
    CHECK_NEAR(copie.getCurrentHitPoint(), 58.0);

    copie.setName("Autre");
    CHECK(original.getName() == "Dracofeu");
}

static void test_le_clone_est_independant_de_l_original()
{
    std::cerr << "test_le_clone_est_independant_de_l_original" << std::endl;

    Pokemon original(6, "Dracofeu", 78.0, 84.0, 78.0, 1);
    std::unique_ptr<Pokemon> copie = original.clone();

    CHECK(copie->getName() == "Dracofeu");
    CHECK(copie.get() != &original);

    copie->takeDamage(78.0);
    CHECK(copie->isKO());
    CHECK(!original.isKO());
}

static void test_le_constructeur_refuse_les_valeurs_invalides()
{
    std::cerr << "test_le_constructeur_refuse_les_valeurs_invalides" << std::endl;

    CHECK_THROWS(Pokemon(0, "Sans numéro", 35.0, 55.0, 40.0, 1), std::invalid_argument);
    CHECK_THROWS(Pokemon(25, "", 35.0, 55.0, 40.0, 1), std::invalid_argument);
    CHECK_THROWS(Pokemon(25, "Pikachu", 0.0, 55.0, 40.0, 1), std::invalid_argument);
    CHECK_THROWS(Pokemon(25, "Pikachu", 35.0, -1.0, 40.0, 1), std::invalid_argument);
    CHECK_THROWS(Pokemon(25, "Pikachu", 35.0, 55.0, 40.0, 0), std::invalid_argument);
    CHECK_THROWS(Pokemon(25, "Pikachu", 35.0, 55.0, 40.0, 1, 25), std::invalid_argument);
}

static void test_les_mutateurs_verifient_leurs_arguments()
{
    std::cerr << "test_les_mutateurs_verifient_leurs_arguments" << std::endl;

    Pokemon p(25, "Pikachu", 35.0, 55.0, 40.0, 1);

    CHECK_THROWS(p.setCurrentHitPoint(-1.0), std::invalid_argument);
    CHECK_THROWS(p.setCurrentHitPoint(36.0), std::invalid_argument);
    CHECK_THROWS(p.setName(""), std::invalid_argument);
    CHECK_THROWS(p.takeDamage(-5.0), std::invalid_argument);

    p.setCurrentHitPoint(10.0);
    CHECK_NEAR(p.getCurrentHitPoint(), 10.0);
}

static void test_une_attaque_retire_les_points_de_vie()
{
    std::cerr << "test_une_attaque_retire_les_points_de_vie" << std::endl;

    Pokemon attaquant(6, "Dracofeu", 78.0, 84.0, 78.0, 1);
    Pokemon cible(143, "Ronflex", 160.0, 110.0, 65.0, 1);

    double degats = attaquant.attackPokemon(cible);

    CHECK_NEAR(degats, 84.0 - 65.0 / 2.0);
    CHECK_NEAR(cible.getCurrentHitPoint(), 160.0 - degats);
}

static void test_les_points_de_vie_ne_descendent_pas_sous_zero()
{
    std::cerr << "test_les_points_de_vie_ne_descendent_pas_sous_zero" << std::endl;

    Pokemon attaquant(6, "Dracofeu", 78.0, 84.0, 78.0, 1);
    Pokemon cible(10, "Chenipan", 45.0, 30.0, 35.0, 1);

    attaquant.attackPokemon(cible);

    CHECK_NEAR(cible.getCurrentHitPoint(), 0.0);
    CHECK(cible.isKO());
    CHECK_NEAR(cible.hitPointRatio(), 0.0);
}

static void test_un_pokemon_ko_ne_subit_ni_ne_porte_d_attaque()
{
    std::cerr << "test_un_pokemon_ko_ne_subit_ni_ne_porte_d_attaque" << std::endl;

    Pokemon vivant(6, "Dracofeu", 78.0, 84.0, 78.0, 1);
    Pokemon ko(10, "Chenipan", 45.0, 30.0, 35.0, 1);
    ko.takeDamage(45.0);

    CHECK_NEAR(vivant.attackPokemon(ko), 0.0);
    CHECK_NEAR(ko.attackPokemon(vivant), 0.0);
    CHECK_NEAR(vivant.getCurrentHitPoint(), 78.0);
    CHECK_NEAR(vivant.attackPokemon(vivant), 0.0);
}

static void test_le_soin_remet_les_points_de_vie_au_maximum()
{
    std::cerr << "test_le_soin_remet_les_points_de_vie_au_maximum" << std::endl;

    Pokemon p(25, "Pikachu", 35.0, 55.0, 40.0, 1);
    p.takeDamage(35.0);
    CHECK(p.isKO());

    p.heal();
    CHECK(!p.isKO());
    CHECK_NEAR(p.getCurrentHitPoint(), 35.0);
}

static void test_le_compteur_suit_les_instances_vivantes()
{
    std::cerr << "test_le_compteur_suit_les_instances_vivantes" << std::endl;

    int depart = Pokemon::getInstanceCount();
    {
        Pokemon p(25, "Pikachu", 35.0, 55.0, 40.0, 1);
        CHECK(Pokemon::getInstanceCount() == depart + 1);

        std::unique_ptr<Pokemon> copie = p.clone();
        CHECK(Pokemon::getInstanceCount() == depart + 2);
    }
    CHECK(Pokemon::getInstanceCount() == depart);

    try
    {
        Pokemon invalide(0, "Sans numéro", 35.0, 55.0, 40.0, 1);
    }
    catch (const std::invalid_argument &)
    {
    }
    CHECK(Pokemon::getInstanceCount() == depart);
}

int main()
{
    Pokemon::showLifeCycle = false;

    test_le_constructeur_initialise_les_attributs();
    test_les_points_de_vie_demarrent_au_maximum();
    test_l_evolution_vaut_zero_par_defaut();
    test_le_constructeur_de_recopie_copie_les_attributs();
    test_le_clone_est_independant_de_l_original();
    test_le_constructeur_refuse_les_valeurs_invalides();
    test_les_mutateurs_verifient_leurs_arguments();
    test_une_attaque_retire_les_points_de_vie();
    test_les_points_de_vie_ne_descendent_pas_sous_zero();
    test_un_pokemon_ko_ne_subit_ni_ne_porte_d_attaque();
    test_le_soin_remet_les_points_de_vie_au_maximum();
    test_le_compteur_suit_les_instances_vivantes();

    return testing::report("test_pokemon");
}
