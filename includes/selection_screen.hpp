#pragma once

#include <map>
#include <string>
#include <vector>
#include <cstddef>
#include "button.hpp"
#include <SFML/Graphics.hpp>
#include "pokemon_attack.hpp"

class SelectionScreen
{
private:
    static constexpr std::size_t PER_PAGE = 12;
    static constexpr std::size_t NO_SLOT = static_cast<std::size_t>(-1);

    Pokemon_Attack &attack;

    // font est déclarée avant buttons : chaque sf::Text garde un pointeur
    // vers elle, elle doit donc vivre plus longtemps que les boutons.
    sf::Font font;
    std::vector<Button> buttons;
    std::map<int, sf::Texture> textures;

    std::size_t page;
    std::size_t selectedSlot;
    std::string message;
    bool done;

    void buildButtons();
    void clickSlot(std::size_t slot);
    void handleClick(sf::Vector2f point);
    void clickParty(std::size_t indexInParty);
    const sf::Texture *textureFor(const Pokemon &pokemon);

    void draw(sf::RenderWindow &window);
    void drawCard(sf::RenderWindow &window, const Pokemon &pokemon,
                  sf::Vector2f position, bool highlighted);
    void drawText(sf::RenderWindow &window, const std::string &text,
                  sf::Vector2f position, unsigned int size, sf::Color color);
    void drawEmptySlot(sf::RenderWindow &window, sf::Vector2f position, std::size_t slot);

public:
    explicit SelectionScreen(Pokemon_Attack &attack);

    void run();
};
