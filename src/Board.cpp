#include "Board.h"

Board::Board(int size)
    : size(size), hits(size, std::vector<bool>(size, false)) {}

bool Board::addShip(std::shared_ptr<Ship> ship) {
    for (int i = 0; i < ship->getLength(); ++i) {
        sf::Vector2i cell = ship->getPosition();
        if (ship->isHorizontal()) cell.x += i;
        else cell.y += i;

        if (cell.x >= size || cell.y >= size || isCellOccupied(cell)) return false;
    }

    ships.push_back(ship);
    return true;
}

bool Board::isCellOccupied(sf::Vector2i cell) const {
    for (const auto& ship : ships) {
        if (ship->occupies(cell)) return true;
    }
    return false;
}

bool Board::isCellHit(sf::Vector2i cell) const {
    return hits[cell.y][cell.x];
}

bool Board::shoot(sf::Vector2i cell) {
    hits[cell.y][cell.x] = true;
    for (const auto& ship : ships) {
        if (ship->occupies(cell)) {
            ship->hitAt(cell);
            return true;
        }
    }
    return false;
}

bool Board::allShipsSunk() const {
    for (const auto& ship : ships) {
        if (!ship->isSunk()) return false;
    }
    return true;
}

void Board::draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset) const {
    // rysowanie siatki
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            sf::RectangleShape tile(sf::Vector2f(tileSize - 1, tileSize - 1));
            tile.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
            tile.setFillColor(hits[y][x] ? sf::Color(200, 100, 100) : sf::Color(180, 220, 250));
            window.draw(tile);
        }
    }

    // rysowanie statków
    for (const auto& ship : ships) {
        ship->draw(window, tileSize, offset);
    }
}
