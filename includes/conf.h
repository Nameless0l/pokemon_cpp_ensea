#pragma once

#define CPP_STANDARD_VERSION 17

#if CPP_STANDARD_VERSION == 17 && __cplusplus < 201703L
#error "Ce projet demande C++17, compilez avec -std=c++17"
#endif

// Chemins relatifs à la racine du projet, d'où le programme doit être lancé
#define ASSET_PATH "assets/"
#define RESOURCE_PATH "data/"
#define POKEDEX_CSV RESOURCE_PATH "pokedex.csv"
#define FONT_FILE ASSET_PATH "font/DejaVuSans.ttf"
#define SPRITE_PATH ASSET_PATH "image/pokemon/"
#define SYSTEM_FONT_FILE "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"

// Fenêtre de sélection du groupe d'attaque
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 770
#define WINDOW_TITLE "Pokémon - Groupe d'attaque"
