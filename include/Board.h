#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Ship.h"

// Klasa Board reprezentuje planszę do gry, zawiera statki i informacje o strzałach
class Board {
private:
    int size; // Rozmiar planszy (np. 10x10)
    
    // Lista statków na planszy (wskazania na obiekty Ship)
    std::vector<std::shared_ptr<Ship>> ships;
    
    // Lista pól, w które oddano strzał, ale nie trafiono
    std::vector<sf::Vector2i> missedShots;
    
    // Lista pól, które zostały trafione
    std::vector<sf::Vector2i> hitMarkers;

public:
    // Konstruktor - tworzy planszę o podanym rozmiarze
    Board(int size);

    // Próbuje dodać statek do planszy; zwraca false, jeśli koliduje z innymi
    bool addShip(std::shared_ptr<Ship> ship);

    // Sprawdza, czy dane pole jest zajęte przez jakiś statek
    bool isCellOccupied(const sf::Vector2i& cell) const;

    // Sprawdza, czy dane pole zostało już trafione
    bool isCellHit(const sf::Vector2i& cell) const;

    // Sprawdza, czy wszystkie statki zostały zatopione
    bool allShipsSunk() const;

    // Przeprowadza atak na dane pole; zwraca true, jeśli trafiono statek
    bool attack(const sf::Vector2i& pos);

    // Rysuje planszę (z opcjonalnym ujawnieniem statków)
    void draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset, bool revealShips) const;

    // Zwraca listę statków na planszy
    std::vector<std::shared_ptr<Ship>> getShips() const { return ships; }

    // Oznacza pole jako trafione lub pudło
    void markShot(sf::Vector2i pos, bool hit);

    // Serializuje informacje o statkach do ciągu znaków (np. do przesyłania przez sieć)
    std::string serializeShips() const;

    // Wczytuje statki z zakodowanego ciągu znaków
    void loadShipsFromString(const std::string& data);
};
