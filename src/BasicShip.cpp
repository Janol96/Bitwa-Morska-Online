#include "BasicShip.h"
#include "TextureManager.h"

BasicShip::BasicShip(int length, sf::Vector2i pos, bool horizontal)
    : Ship(length, pos, horizontal) {}

void BasicShip::draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset) const {
    sf::Sprite sprite;
    sprite.setTexture(TextureManager::getShipTexture(length));
    sprite.setScale(tileSize / 40.f, tileSize / 40.f);
    sprite.setPosition(offset.x + position.x * tileSize, offset.y + position.y * tileSize);

    if (!horizontal) {
        // Ustaw środek jako punkt obrotu
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

        // Obrót o 90 stopni
        sprite.setRotation(90.f);

        // Przesuń sprite z powrotem, żeby środek był nad pierwszym polem
        sprite.setPosition(
            offset.x + position.x * tileSize + tileSize / 2,
            offset.y + position.y * tileSize + tileSize * length / 2.0f
            );
    }

    window.draw(sprite);
}
