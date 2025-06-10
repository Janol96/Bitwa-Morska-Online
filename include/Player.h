#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <string>

class Player {
private:
    std::string name;
    Board board;
    sf::Font& font;

public:
    Player(const std::string& name);
    Player(Board& board, sf::Font& font);

    Board& getBoard();
    const Board& getBoard() const;

    void addShip(std::shared_ptr<Ship> ship);
    std::vector<std::shared_ptr<Ship>> getShips() const;
};
