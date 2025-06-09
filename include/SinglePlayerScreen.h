#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "Player.h"

class SinglePlayerScreen {
private:
    sf::Font& font;
    Player player;

    int currentShipLength;
    bool currentOrientation;

    std::optional<sf::Vector2i> ghostPosition; // aktualna pozycja kursora

public:
    SinglePlayerScreen(sf::Font& font);
    void run(sf::RenderWindow& window);
};
