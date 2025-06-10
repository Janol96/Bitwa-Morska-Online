#include "BasicShip.h"

BasicShip::BasicShip(int length, sf::Vector2i pos, bool horizontal)
    : Ship(length, pos, horizontal) {}

void BasicShip::draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset) const {
    for (int i = 0; i < length; ++i) {
        int x = position.x + (horizontal ? i : 0);
        int y = position.y + (horizontal ? 0 : i);

        sf::RectangleShape shape(sf::Vector2f(tileSize - 4, tileSize - 4));
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(offset.x + x * tileSize + 2, offset.y + y * tileSize + 2);
        window.draw(shape);
    }
}
