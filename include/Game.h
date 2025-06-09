#pragma once
#include "Player.h"
#include "AIPlayer.h"

class Game {
private:
    Player& human;
    AIPlayer ai;
    bool playerTurn;

public:
    Game(Player& humanPlayer);

    void run(sf::RenderWindow& window);
    void drawBoards(sf::RenderWindow& window, float tileSize, sf::Vector2f offsetPlayer, sf::Vector2f offsetAI);
};
