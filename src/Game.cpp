#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game(Player& humanPlayer)
    : human(humanPlayer), ai("Komputer"), playerTurn(true)
{
    ai.placeShipsRandomly();
}

void Game::run(sf::RenderWindow& window) {
    float tileSize = 40.f;
    sf::Vector2f offsetPlayer(50, 50);
    sf::Vector2f offsetAI(550, 50);

    bool running = true;
    bool playerWon = false;

    while (running && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left &&
                playerTurn) {

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int x = (mousePos.x - static_cast<int>(offsetAI.x)) / (int)tileSize;
                int y = (mousePos.y - static_cast<int>(offsetAI.y)) / (int)tileSize;

                if (x >= 0 && x < 10 && y >= 0 && y < 10) {
                    ai.getBoard().attack(sf::Vector2i(x, y));
                    playerTurn = false;
                }
            }
        }

        if (!playerTurn) {
            sf::Vector2i aiShot = ai.chooseShot();
            human.getBoard().attack(aiShot);
            playerTurn = true;
        }

        if (ai.getBoard().allShipsSunk()) {
            playerWon = true;
            running = false;
        } else if (human.getBoard().allShipsSunk()) {
            playerWon = false;
            running = false;
        }

        window.clear();
        drawBoards(window, tileSize, offsetPlayer, offsetAI);
        window.display();
    }

    // Ekran końcowy
    sf::Font endFont;
    endFont.loadFromFile("Roboto-Regular.ttf");

    sf::Text endText;
    endText.setFont(endFont);
    endText.setCharacterSize(64);
    endText.setFillColor(playerWon ? sf::Color::Green : sf::Color::Red);
    endText.setString(playerWon ? "WYGRANA!" : "PRZEGRANA!");
    endText.setPosition(300, 400);

    bool wait = true;
    while (wait && window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            if (e.type == sf::Event::MouseButtonPressed) wait = false;
        }

        window.clear();
        drawBoards(window, tileSize, offsetPlayer, offsetAI);
        window.draw(endText);
        window.display();
    }
}

void Game::drawBoards(sf::RenderWindow& window, float tileSize, sf::Vector2f offsetPlayer, sf::Vector2f offsetAI) {
    human.getBoard().draw(window, tileSize, offsetPlayer, true);
    ai.getBoard().draw(window, tileSize, offsetAI, false);
}
