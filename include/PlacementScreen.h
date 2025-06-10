#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "Player.h"

class PlacementScreen {
private:
    sf::Font& font;
    Player& player;
    int currentShipLength;
    bool currentOrientation;
    std::optional<sf::Vector2i> ghostPosition;

public:
    PlacementScreen(sf::Font& font, Player& player);
    void run(sf::RenderWindow& window);
};
