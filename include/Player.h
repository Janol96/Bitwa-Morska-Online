#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include <string>

// Klasa Player reprezentuje gracza w grze, posiada planszę i nazwę
class Player {
private:
    std::string name;     // Nazwa gracza
    Board board;          // Plansza gracza z rozmieszczonymi statkami
    sf::Font& font;       // Referencja do czcionki (do wyświetlania tekstu, np. nazw)

public:
    // Konstruktor - tworzy gracza z nazwą (używany np. dla AI, bez fontu)
    Player(const std::string& name);

    // Konstruktor - tworzy gracza z istniejącą planszą i czcionką (używany np. w grze lokalnej)
    Player(Board& board, sf::Font& font);

    // Zwraca referencję do planszy (umożliwia modyfikację)
    Board& getBoard();

    // Zwraca stałą referencję do planszy (do odczytu)
    const Board& getBoard() const;

    // Dodaje statek do planszy gracza
    void addShip(std::shared_ptr<Ship> ship);

    // Zwraca listę statków gracza
    std::vector<std::shared_ptr<Ship>> getShips() const;
};
