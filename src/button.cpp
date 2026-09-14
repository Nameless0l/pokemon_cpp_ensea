#include "button.hpp"

Button::Button(const sf::Font &font, const std::string &text, sf::Vector2f position,
               sf::Vector2f size, std::function<void()> action)
    : box(size), label(utf8(text), font, 16), action(std::move(action))
{
    box.setPosition(position);
    box.setFillColor(sf::Color(58, 62, 82));
    box.setOutlineThickness(1.0f);
    box.setOutlineColor(sf::Color(120, 126, 150));

    sf::FloatRect bounds = label.getLocalBounds();
    label.setPosition(position.x + (size.x - bounds.width) / 2.0f - bounds.left,
                      position.y + (size.y - bounds.height) / 2.0f - bounds.top);
}

bool Button::handleClick(sf::Vector2f point)
{
    if (!box.getGlobalBounds().contains(point))
    {
        return false;
    }

    if (action)
    {
        action();
    }
    return true;
}

void Button::draw(sf::RenderWindow &window) const
{
    window.draw(box);
    window.draw(label);
}
