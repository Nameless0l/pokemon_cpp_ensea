# Pokemon Selector — Introduction à la POO en C++ (IS_3436)

TP de 3ème année IS — ENSEA, hiver 2025-2026.
Moteur de jeu Pokémon en C++17 avec interface graphique SFML.

## Dépendances

- `g++` avec support C++17
- SFML 2.5 (`sudo apt-get install libsfml-dev`)
- Optionnel : `valgrind` pour la recherche de fuites mémoire

## Compilation et exécution

| Commande | Effet |
| --- | --- |
| `make` | compile `bin/main.exe` |
| `make run` | compile puis lance le programme |
| `make test` | compile et exécute tous les `tests/test_*.cpp` |
| `make sanitize` | recompile les tests avec ASan/UBSan et les exécute |
| `make valgrind` | passe chaque test sous Valgrind |
| `make clean` | supprime `bin/` |

Aucun fichier n'est listé à la main dans le Makefile : ajouter un `src/*.cpp`
ou un `tests/test_*.cpp` suffit.

## Structure

```
.
├── includes/        # fichiers .hpp (une classe = un fichier)
├── src/             # implémentations .cpp + main.cpp
├── tests/           # tests unitaires test_*.cpp
├── data/            # pokedex.csv
├── assets/image/    # sprites des Pokémon + éléments d'interface
└── bin/             # produits de compilation (non versionnés)
```

Format de `data/pokedex.csv` :

```
#,Name,Type 1,Type 2,Total,HP,Attack,Defense,Sp. Atk,Sp. Def,Speed,Generation,Legendary
1,Bulbasaur,Grass,Poison,318,45,49,49,65,65,45,1,False
```

Le sprite d'un Pokémon est `assets/image/pokemon/<numéro>.png`.

## Classes

- `Pokemon` — numéro, nom, évolution, PV max / courants, attaque, défense, méthode d'attaque.
- `Pokemon_Vector` — classe abstraite représentant une liste de Pokémon.
- `Pokedex` — hérite de `Pokemon_Vector`, singleton construit à partir du CSV ;
  ses données sont inaccessibles, on n'en extrait que des clones.
- `Pokemon_Party` — hérite de `Pokemon_Vector`, l'ensemble des Pokémon du joueur, sans limite de taille.
- `Pokemon_Attack` — hérite de `Pokemon_Vector`, extrait de 6 Pokémon de la `Pokemon_Party`.

## Règle d'attaque

_À compléter._

## Graphe d'états (design pattern STATE)

_À compléter : description des états du moteur de jeu et de leurs transitions._
