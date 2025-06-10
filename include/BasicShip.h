#pragma once
#include "Ship.h"

class BasicShip : public Ship {
public:
    BasicShip(int length, sf::Vector2i pos, bool horizontal);
    void draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset) const override;
};
