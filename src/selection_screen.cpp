#include "conf.h"
#include <stdexcept>
#include "selection_screen.hpp"

static const float CARD_WIDTH = 110.0f;
static const float CARD_HEIGHT = 140.0f;
static const float GRID_X = 30.0f;
static const float GRID_Y = 80.0f;
static const float COLUMN_STEP = 120.0f;
static const float ROW_STEP = 150.0f;
static const std::size_t GRID_COLUMNS = 4;

static const float SLOT_Y = 600.0f;
static const float PANEL_X = 560.0f;

SelectionScreen::SelectionScreen(Pokemon_Attack &attack)
    : attack(attack), page(0), selectedSlot(NO_SLOT), done(false)
{
    if (!font.loadFromFile(FONT_FILE) && !font.loadFromFile(SYSTEM_FONT_FILE))
    {
        throw std::runtime_error("Police introuvable : " FONT_FILE);
    }
}

const sf::Texture *SelectionScreen::textureFor(const Pokemon &pokemon)
{
    int id = pokemon.getId();

    std::map<int, sf::Texture>::iterator found = textures.find(id);
    if (found != textures.end())
    {
        return &found->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(SPRITE_PATH + std::to_string(id) + ".png"))
    {
        return nullptr;
    }
    texture.setSmooth(true);

    return &textures.emplace(id, std::move(texture)).first->second;
}

void SelectionScreen::buildButtons()
{
    sf::Vector2f size(280.0f, 42.0f);

    buttons.emplace_back(font, "Page précédente", sf::Vector2f(PANEL_X, 90.0f), size,
                         [this]() { if (page > 0) { page--; } });

    buttons.emplace_back(font, "Page suivante", sf::Vector2f(PANEL_X, 142.0f), size,
                         [this]()
                         {
                             if ((page + 1) * PER_PAGE < attack.getParty().size()) { page++; }
                         });

    buttons.emplace_back(font, "Retirer le Pokémon sélectionné", sf::Vector2f(PANEL_X, 210.0f), size,
                         [this]()
                         {
                             if (selectedSlot == NO_SLOT || selectedSlot >= attack.size())
                             {
                                 message = "Sélectionnez d'abord un Pokémon du groupe.";
                                 return;
                             }
                             message = attack.peek(selectedSlot)->getName() + " retourne dans l'équipe.";
                             attack.giveBack(selectedSlot);
                             selectedSlot = NO_SLOT;
                         });

    buttons.emplace_back(font, "Tout rendre à l'équipe", sf::Vector2f(PANEL_X, 262.0f), size,
                         [this]()
                         {
                             attack.giveBackAll();
                             selectedSlot = NO_SLOT;
                             message = "Groupe d'attaque vidé.";
                         });

    buttons.emplace_back(font, "Valider et fermer", sf::Vector2f(PANEL_X, 330.0f), size,
                         [this]() { done = true; });
}

void SelectionScreen::clickParty(std::size_t indexInParty)
{
    try
    {
        message = attack.getParty().peek(indexInParty)->getName() + " rejoint le groupe d'attaque.";
        attack.addFromParty(indexInParty);
    }
    catch (const std::length_error &)
    {
        message = "Le groupe d'attaque est déjà complet (6 Pokémon).";
    }
}

void SelectionScreen::clickSlot(std::size_t slot)
{
    if (slot >= attack.size())
    {
        message = "Cet emplacement est vide.";
        return;
    }

    if (selectedSlot == NO_SLOT)
    {
        selectedSlot = slot;
        message = attack.peek(slot)->getName() + " sélectionné. Cliquez un autre emplacement pour l'échanger.";
        return;
    }

    if (selectedSlot == slot)
    {
        selectedSlot = NO_SLOT;
        message = "Sélection annulée.";
        return;
    }

    attack.swapPositions(selectedSlot, slot);
    message = "Positions échangées.";
    selectedSlot = NO_SLOT;
}

void SelectionScreen::handleClick(sf::Vector2f point)
{
    for (Button &button : buttons)
    {
        if (button.handleClick(point))
        {
            return;
        }
    }

    Pokemon_Party &party = attack.getParty();

    for (std::size_t visible = 0; visible < PER_PAGE; visible++)
    {
        std::size_t indexInParty = page * PER_PAGE + visible;
        if (indexInParty >= party.size())
        {
            break;
        }

        float x = GRID_X + static_cast<float>(visible % GRID_COLUMNS) * COLUMN_STEP;
        float y = GRID_Y + static_cast<float>(visible / GRID_COLUMNS) * ROW_STEP;

        if (sf::FloatRect(x, y, CARD_WIDTH, CARD_HEIGHT).contains(point))
        {
            clickParty(indexInParty);
            return;
        }
    }

    for (std::size_t slot = 0; slot < Pokemon_Attack::MAX_SIZE; slot++)
    {
        float x = GRID_X + static_cast<float>(slot) * COLUMN_STEP;

        if (sf::FloatRect(x, SLOT_Y, CARD_WIDTH, CARD_HEIGHT).contains(point))
        {
            clickSlot(slot);
            return;
        }
    }
}

void SelectionScreen::drawText(sf::RenderWindow &window, const std::string &text,
                               sf::Vector2f position, unsigned int size, sf::Color color)
{
    sf::Text drawn(utf8(text), font, size);
    drawn.setPosition(position);
    drawn.setFillColor(color);
    window.draw(drawn);
}

void SelectionScreen::drawCard(sf::RenderWindow &window, const Pokemon &pokemon,
                               sf::Vector2f position, bool highlighted)
{
    sf::RectangleShape card(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
    card.setPosition(position);
    card.setFillColor(sf::Color(44, 47, 64));
    card.setOutlineThickness(highlighted ? 3.0f : 1.0f);
    card.setOutlineColor(highlighted ? sf::Color(250, 205, 70) : sf::Color(96, 100, 124));
    window.draw(card);

    const sf::Texture *texture = textureFor(pokemon);
    if (texture != nullptr)
    {
        sf::Sprite sprite(*texture);
        sprite.setPosition(position.x + 7.0f, position.y + 4.0f);
        window.draw(sprite);
    }
    else
    {
        drawText(window, "#" + std::to_string(pokemon.getId()),
                 sf::Vector2f(position.x + 12.0f, position.y + 40.0f), 16, sf::Color(150, 150, 170));
    }

    drawText(window, pokemon.getName(), sf::Vector2f(position.x + 8.0f, position.y + 100.0f),
             13, sf::Color::White);

    drawText(window, std::to_string(static_cast<int>(pokemon.getCurrentHitPoint())) + " PV",
             sf::Vector2f(position.x + 8.0f, position.y + 118.0f), 12, sf::Color(150, 220, 150));
}

void SelectionScreen::drawEmptySlot(sf::RenderWindow &window, sf::Vector2f position, std::size_t slot)
{
    sf::RectangleShape card(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
    card.setPosition(position);
    card.setFillColor(sf::Color(32, 34, 46));
    card.setOutlineThickness(1.0f);
    card.setOutlineColor(sf::Color(70, 74, 92));
    window.draw(card);

    drawText(window, std::to_string(slot + 1), sf::Vector2f(position.x + 48.0f, position.y + 52.0f),
             24, sf::Color(80, 84, 104));
}

void SelectionScreen::draw(sf::RenderWindow &window)
{
    Pokemon_Party &party = attack.getParty();

    while (page > 0 && page * PER_PAGE >= party.size())
    {
        page--;
    }

    window.clear(sf::Color(24, 26, 36));

    drawText(window, "Composez votre groupe d'attaque", sf::Vector2f(GRID_X, 22.0f), 22, sf::Color::White);
    drawText(window, "Équipe (" + std::to_string(party.size()) + " Pokémon)",
             sf::Vector2f(GRID_X, 54.0f), 15, sf::Color(160, 165, 190));

    for (std::size_t visible = 0; visible < PER_PAGE; visible++)
    {
        std::size_t indexInParty = page * PER_PAGE + visible;
        if (indexInParty >= party.size())
        {
            break;
        }

        sf::Vector2f position(GRID_X + static_cast<float>(visible % GRID_COLUMNS) * COLUMN_STEP,
                              GRID_Y + static_cast<float>(visible / GRID_COLUMNS) * ROW_STEP);
        drawCard(window, *party.peek(indexInParty), position, false);
    }

    drawText(window, "Groupe d'attaque (" + std::to_string(attack.size()) + " / 6)",
             sf::Vector2f(GRID_X, SLOT_Y - 26.0f), 15, sf::Color(160, 165, 190));

    for (std::size_t slot = 0; slot < Pokemon_Attack::MAX_SIZE; slot++)
    {
        sf::Vector2f position(GRID_X + static_cast<float>(slot) * COLUMN_STEP, SLOT_Y);

        if (slot < attack.size())
        {
            drawCard(window, *attack.peek(slot), position, slot == selectedSlot);
        }
        else
        {
            drawEmptySlot(window, position, slot);
        }
    }

    drawText(window, message, sf::Vector2f(GRID_X, 545.0f), 14, sf::Color(250, 205, 70));

    drawText(window, "Clic sur un Pokémon de l'équipe : il rejoint le groupe.",
             sf::Vector2f(PANEL_X, 400.0f), 13, sf::Color(150, 155, 180));
    drawText(window, "Clic sur deux emplacements du groupe :",
             sf::Vector2f(PANEL_X, 424.0f), 13, sf::Color(150, 155, 180));
    drawText(window, "leurs positions sont échangées.",
             sf::Vector2f(PANEL_X, 444.0f), 13, sf::Color(150, 155, 180));

    for (const Button &button : buttons)
    {
        button.draw(window);
    }

    window.display();
}

void SelectionScreen::run()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    window.setFramerateLimit(60);

    buildButtons();
    message = "Cliquez sur un Pokémon de votre équipe pour l'ajouter.";
    done = false;

    while (window.isOpen() && !done)
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed &&
                     event.mouseButton.button == sf::Mouse::Left)
            {
                handleClick(window.mapPixelToCoords(
                    sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
            }
        }

        if (window.isOpen())
        {
            draw(window);
        }
    }

    buttons.clear();
}
