#include "Board.h"
#include <sstream>
#include "BasicShip.h"

Board::Board(int size) : size(size) {}

bool Board::addShip(std::shared_ptr<Ship> ship) {
    for (int i = 0; i < ship->getLength(); ++i) {
        int x = ship->getPosition().x + (ship->isHorizontal() ? i : 0);
        int y = ship->getPosition().y + (ship->isHorizontal() ? 0 : i);
        if (x >= size || y >= size || isCellOccupied(sf::Vector2i(x, y))) {
            return false;
        }
    }

    ships.push_back(ship);
    return true;
}

bool Board::isCellOccupied(const sf::Vector2i& cell) const {
    for (const auto& ship : ships) {
        if (ship->occupies(cell)) return true;
    }
    return false;
}

bool Board::isCellHit(const sf::Vector2i& cell) const {
    for (const auto& ship : ships) {
        if (ship->occupies(cell)) {
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

bool Board::attack(const sf::Vector2i& pos) {
    for (const auto& ship : ships) {
        if (ship->occupies(pos)) {
            ship->hitAt(pos);
            hitMarkers.push_back(pos);
            return true;
        }
    }

    missedShots.push_back(pos);
    return false;
}

void Board::markShot(sf::Vector2i pos, bool hit) {
    if (hit) {
        hitMarkers.push_back(pos);
    } else {
        missedShots.push_back(pos);
    }
}

void Board::draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset, bool revealShips) const {
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            sf::RectangleShape cell(sf::Vector2f(tileSize - 2, tileSize - 2));
            cell.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
            cell.setFillColor(sf::Color(173, 216, 230));
            window.draw(cell);
        }
    }

    for (const auto& ship : ships) {
        if (revealShips || ship->isSunk()) {
            ship->draw(window, tileSize, offset);
        }
    }

    for (const auto& hit : hitMarkers) {
        sf::RectangleShape line1(sf::Vector2f(tileSize - 10, 3));
        line1.setFillColor(sf::Color::Red);
        line1.setPosition(offset.x + hit.x * tileSize + 5, offset.y + hit.y * tileSize + 5);
        line1.setRotation(45);

        sf::RectangleShape line2 = line1;
        line2.setRotation(-45);

        window.draw(line1);
        window.draw(line2);
    }

    for (const auto& miss : missedShots) {
        sf::CircleShape dot(tileSize / 6);
        dot.setFillColor(sf::Color(100, 100, 100, 180));
        dot.setPosition(offset.x + miss.x * tileSize + tileSize / 3, offset.y + miss.y * tileSize + tileSize / 3);
        window.draw(dot);
    }
}

std::string Board::serializeShips() const {
    std::ostringstream oss;
    for (const auto& ship : ships) {
        sf::Vector2i pos = ship->getPosition();
        int length = ship->getLength();
        bool horiz = ship->isHorizontal();

        oss << length << "," << pos.x << "," << pos.y << "," << (horiz ? 1 : 0) << ";";
    }
    return oss.str();
}

void Board::loadShipsFromString(const std::string& data) {
    ships.clear();  // lub reset()

    std::istringstream iss(data);
    std::string token;

    while (std::getline(iss, token, ';')) {
        if (token.empty()) continue;

        std::istringstream part(token);
        std::string val;
        std::vector<int> parts;

        while (std::getline(part, val, ',')) {
            parts.push_back(std::stoi(val));
        }

        if (parts.size() == 4) {
            int length = parts[0];
            sf::Vector2i pos(parts[1], parts[2]);
            bool horiz = parts[3];

            addShip(std::make_shared<BasicShip>(length, pos, horiz));
        }
    }
}
