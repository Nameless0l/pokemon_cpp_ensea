#pragma once

#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

inline sf::String utf8(const std::string &text)
{
    return sf::String::fromUtf8(text.begin(), text.end());
}

class Button
{
private:
    sf::RectangleShape box;
    sf::Text label;
    // L'action est fournie par l'appelant sous forme de lambda.
    std::function<void()> action;

public:
    Button(const sf::Font &font, const std::string &text, sf::Vector2f position,
           sf::Vector2f size, std::function<void()> action);

    bool handleClick(sf::Vector2f point);
    void draw(sf::RenderWindow &window) const;
};
