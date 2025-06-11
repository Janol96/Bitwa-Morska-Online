#include "Ship.h"
#include "TextureManager.h"

// Konstruktor klasy Ship - ustawia długość statku, jego pozycję oraz orientację (poziomą/pionową)
// Inicjalizuje wektor 'hits' jako tablicę fałszywych wartości (brak trafień)
Ship::Ship(int length, sf::Vector2i pos, bool horizontal)
    : length(length), horizontal(horizontal), position(pos), hits(length, false) {}

// Zwraca długość statku
int Ship::getLength() const {
    return length;
}

// Zwraca pozycję początkową statku (lewy górny róg)
sf::Vector2i Ship::getPosition() const {
    return position;
}

// Zwraca informację o orientacji statku: true = poziomy, false = pionowy
bool Ship::isHorizontal() const {
    return horizontal;
}

// Sprawdza, czy wszystkie segmenty statku zostały trafione
bool Ship::isSunk() const {
    for (bool hit : hits) {
        if (!hit) return false; // Jeśli którykolwiek segment nie został trafiony, statek nie jest zatopiony
    }
    return true; // Wszystkie segmenty trafione - statek zatopiony
}

// Sprawdza, czy dany punkt planszy jest zajmowany przez ten statek
bool Ship::occupies(sf::Vector2i cell) const {
    for (int i = 0; i < length; ++i) {
        int x = position.x + (horizontal ? i : 0);
        int y = position.y + (horizontal ? 0 : i);
        if (cell == sf::Vector2i(x, y)) return true; // Trafiono na jeden z segmentów statku
    }
    return false;
}

// Oznacza dany segment statku jako trafiony, jeśli pasuje do współrzędnej
void Ship::hitAt(sf::Vector2i cell) {
    for (int i = 0; i < length; ++i) {
        int x = position.x + (horizontal ? i : 0);
        int y = position.y + (horizontal ? 0 : i);
        if (cell == sf::Vector2i(x, y)) {
            hits[i] = true; // Ustawia flagę trafienia dla danego segmentu
            break;
        }
    }
}

// Rysuje statek na podanym oknie SFML
void Ship::draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset) const {
    sf::Sprite sprite;
    
    // Pobiera odpowiednią teksturę statku z TextureManagera na podstawie długości
    sprite.setTexture(TextureManager::getShipTexture(length));

    // Skaluje sprite do rozmiaru odpowiadającego pojedynczemu polu na planszy
    sprite.setScale(tileSize / 40.f, tileSize / 40.f);

    // Ustawia pozycję sprite'a na planszy (z uwzględnieniem offsetu)
    sprite.setPosition(offset.x + position.x * tileSize, offset.y + position.y * tileSize);

    // Jeśli statek jest pionowy, obraca sprite o 90 stopni i przesuwa go w dół,
    // żeby wyrównać pozycję
    if (!horizontal) {
        sprite.setRotation(90.f);
        sprite.setOrigin(0.f, 0.f);
        sprite.move(0, -length * tileSize + tileSize);
    }

    // Rysuje sprite na ekranie
    window.draw(sprite);
}
