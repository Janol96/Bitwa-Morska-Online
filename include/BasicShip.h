#pragma once

#include "Ship.h"

// Klasa BasicShip dziedziczy po klasie Ship
// Reprezentuje podstawową wersję statku, który można narysować na planszy
class BasicShip : public Ship {
public:
    // Konstruktor - tworzy statek o podanej długości, pozycji i orientacji
    BasicShip(int length, sf::Vector2i pos, bool horizontal);

    // Rysuje statek na podanym oknie SFML
    // tileSize - rozmiar jednego pola planszy
    // offset - przesunięcie planszy względem okna
    void draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset) const override;
};
