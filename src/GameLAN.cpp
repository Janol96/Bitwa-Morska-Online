#include "GameLAN.h"
#include "BasicShip.h"
#include "PlacementScreen.h"
#include <thread>
#include <chrono>

GameLAN::GameLAN(Player& player, Player& enemy, NetworkManager& network, bool isServer, sf::Font& font)
    : player(player), enemy(enemy), network(network), isServer(isServer), font(font) {
    myTurn = isServer;
}

void GameLAN::run(sf::RenderWindow& window) {
    this->window = &window;
    startPlacementPhase();

    float tileSize = 40.f;
    sf::Vector2f offsetPlayer(50, 50);
    sf::Vector2f offsetEnemy(500, 50);

    sf::Text endText;
    endText.setFont(font);
    endText.setCharacterSize(50);
    endText.setFillColor(sf::Color::White);
    endText.setPosition(250, 400);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!gameOver && myTurn && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int x = (mousePos.x - (int)offsetEnemy.x) / (int)tileSize;
                int y = (mousePos.y - (int)offsetEnemy.y) / (int)tileSize;

                if (x >= 0 && x < 10 && y >= 0 && y < 10) {
                    sf::Vector2i shot(x, y);
                    network.sendShot(shot);

                    bool hit;
                    network.receiveShotResult(hit);
                    enemy.getBoard().markShot(shot, hit);
                    myTurn = false;
                }
            }

            if (gameOver && event.type == sf::Event::MouseButtonPressed)
                return;
        }

        if (!gameOver && !myTurn) {
            sf::Vector2i enemyShot;
            if (network.receiveShot(enemyShot)) {
                bool hit = player.getBoard().attack(enemyShot);
                network.sendShotResult(hit);
                myTurn = true;
            }
        }

        if (!gameOver && (player.getBoard().allShipsSunk() || enemy.getBoard().allShipsSunk())) {
            gameOver = true;
            iWon = enemy.getBoard().allShipsSunk();
            endText.setString(iWon ? "WYGRANA" : "PRZEGRANA");
        }

        window.clear(sf::Color::Black);
        player.getBoard().draw(window, tileSize, offsetPlayer, true);
        enemy.getBoard().draw(window, tileSize, offsetEnemy, false);

        if (gameOver)
            window.draw(endText);

        window.display();
    }
}
void GameLAN::startPlacementPhase() {
    PlacementScreen placement(font, player);
    placement.run(*window);

    placementDone = true;
    network.sendMessage("PLACEMENT_DONE");

    std::string shipData = player.getBoard().serializeShips();
    network.sendMessage("SHIPS:" + shipData);

    while (!opponentPlacementDone) {
        handleIncomingMessagesDuringPlacement();
        sf::sleep(sf::milliseconds(100));
    }
}

void GameLAN::handleIncomingMessagesDuringPlacement() {
    std::string message;
    if (network.receiveMessage(message)) {
        if (message == "PLACEMENT_DONE") {
            opponentPlacementDone = true;
        } else if (message.rfind("SHIPS:", 0) == 0) {
            std::string data = message.substr(6);
            enemy.getBoard().loadShipsFromString(data);
        }
    }
}
