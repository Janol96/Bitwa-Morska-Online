#include "Ship.h"

Ship::Ship(int length, sf::Vector2i pos, bool horizontal)
    : length(length), horizontal(horizontal), position(pos), hits(length, false) {}

int Ship::getLength() const {
    return length;
}

sf::Vector2i Ship::getPosition() const {
    return position;
}

bool Ship::isHorizontal() const {
    return horizontal;
}

bool Ship::isSunk() const {
    for (bool hit : hits) {
        if (!hit) return false;
    }
    return true;
}

bool Ship::occupies(sf::Vector2i cell) const {
    for (int i = 0; i < length; ++i) {
        int x = position.x + (horizontal ? i : 0);
        int y = position.y + (horizontal ? 0 : i);
        if (cell == sf::Vector2i(x, y)) return true;
    }
    return false;
}

void Ship::hitAt(sf::Vector2i cell) {
    for (int i = 0; i < length; ++i) {
        int x = position.x + (horizontal ? i : 0);
        int y = position.y + (horizontal ? 0 : i);
        if (cell == sf::Vector2i(x, y)) {
            hits[i] = true;
            break;
        }
    }
}
