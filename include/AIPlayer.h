#pragma once

#include "Player.h"
#include <set>

// Klasa AIPlayer dziedziczy po klasie Player i reprezentuje przeciwnika sterowanego przez komputer
class AIPlayer : public Player {
private:
    // Zbiór współrzędnych, w które AI już strzelało (aby uniknąć powtórzeń)
    std::set<std::pair<int, int>> shotsFired;

public:
    // Konstruktor - inicjalizuje gracza AI z podaną nazwą
    AIPlayer(const std::string& name);

    // Rozmieszcza statki losowo na planszy
    void placeShipsRandomly();

    // Wybiera nowe pole do strzału (takie, w które jeszcze nie strzelał)
    sf::Vector2i chooseShot();
};
