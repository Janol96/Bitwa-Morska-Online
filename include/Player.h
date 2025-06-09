#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Ship.h"

class Player {
protected:
    Board board;
    std::string name;

public:
    Player(const std::string& name);

    virtual ~Player() = default;

    Board& getBoard();
    const Board& getBoard() const;

    const std::string& getName() const;

    virtual void placeShips(); // tymczasowa metoda rozmieszczania
    virtual sf::Vector2i chooseTarget(); // wybór celu (np. przez AI)
    virtual void notifyShotResult(bool hit); // AI może się uczyć
};
