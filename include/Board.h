#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Ship.h"

class Board {
private:
    int size;
    std::vector<std::shared_ptr<Ship>> ships;
    std::vector<sf::Vector2i> missedShots;
    std::vector<sf::Vector2i> hitMarkers;

public:
    Board(int size);

    bool addShip(std::shared_ptr<Ship> ship);
    bool isCellOccupied(const sf::Vector2i& cell) const;
    bool isCellHit(const sf::Vector2i& cell) const;
    bool allShipsSunk() const;
    bool attack(const sf::Vector2i& pos);

    void draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset, bool revealShips) const;

    std::vector<std::shared_ptr<Ship>> getShips() const { return ships; }

    void markShot(sf::Vector2i pos, bool hit);

    std::string serializeShips() const;
    void loadShipsFromString(const std::string& data);
};
