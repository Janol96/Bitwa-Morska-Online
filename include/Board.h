#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Ship.h"

class Board {
private:
    int size;
    std::vector<std::shared_ptr<Ship>> ships;
    std::vector<std::vector<bool>> hits; // śledzenie trafień

public:
    Board(int size = 10);

    bool addShip(std::shared_ptr<Ship> ship);
    bool isCellOccupied(sf::Vector2i cell) const;
    bool isCellHit(sf::Vector2i cell) const;

    bool shoot(sf::Vector2i cell); // true jeśli trafiono
    bool allShipsSunk() const;

    void draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset) const;
};
