#pragma once

#include "Player.h"
#include "AIPlayer.h"

// Klasa Game zarządza rozgrywką między graczem a AI
class Game {
private:
    Player& human;     // Referencja do gracza (człowieka)
    AIPlayer ai;       // Obiekt przeciwnika sterowanego przez komputer
    bool playerTurn;   // Flaga określająca, czy teraz jest tura gracza

public:
    // Konstruktor - inicjalizuje grę z podanym graczem
    Game(Player& humanPlayer);

    // Główna pętla gry (obsługuje logikę i zdarzenia)
    void run(sf::RenderWindow& window);

    // Rysuje obie plansze: gracza i AI (z przesunięciem i skalą)
    void drawBoards(sf::RenderWindow& window, float tileSize, sf::Vector2f offsetPlayer, sf::Vector2f offsetAI);
};
