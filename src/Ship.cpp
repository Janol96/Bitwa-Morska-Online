#include "Ship.h"
#include "TextureManager.h"  // dodane

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

void Ship::draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset) const {
    sf::Sprite sprite;
    sprite.setTexture(TextureManager::getShipTexture(length));

    sprite.setScale(tileSize / 40.f, tileSize / 40.f);
    sprite.setPosition(offset.x + position.x * tileSize, offset.y + position.y * tileSize);

    if (!horizontal) {
        sprite.setRotation(90.f);
        sprite.setOrigin(0.f, 0.f);
        sprite.move(0, -length * tileSize + tileSize);
    }

    window.draw(sprite);
}
