#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "NetworkManager.h"

class GameLAN {
    Player& player;
    Player& enemy;
    NetworkManager& network;
    bool isServer;
    bool myTurn;
    sf::Font& font;

    bool gameOver = false;
    bool iWon = false;
    bool placementDone = false;
    bool opponentPlacementDone = false;
    sf::RenderWindow* window = nullptr;

public:
    GameLAN(Player& player, Player& enemy, NetworkManager& network, bool isServer, sf::Font& font);
    void run(sf::RenderWindow& window);
    void startPlacementPhase();
    void handleIncomingMessagesDuringPlacement();
};
