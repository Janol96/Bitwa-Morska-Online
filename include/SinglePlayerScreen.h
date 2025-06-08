#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Ship.h"

class SinglePlayerScreen {
private:
    Board board;
    sf::Font& font;

public:
    SinglePlayerScreen(sf::Font& font);
    void run(sf::RenderWindow& window);
};
