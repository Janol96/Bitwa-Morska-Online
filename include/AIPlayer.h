#pragma once
#include "Player.h"
#include <set>

class AIPlayer : public Player {
private:
    std::set<std::pair<int, int>> shotsFired;

public:
    AIPlayer(const std::string& name);
    void placeShipsRandomly();
    sf::Vector2i chooseShot();
};
