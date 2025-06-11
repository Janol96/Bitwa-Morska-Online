#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

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

    // Wczytaj tło
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("menu_bg_clear.png")) {
        std::cerr << "Nie udało się załadować assets/menu_bg_clear.png\n";
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    while (running && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left && playerTurn) {

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

        // Rysowanie
        window.clear();
        window.draw(backgroundSprite);

        human.getBoard().draw(window, tileSize, offsetPlayer, true);
        ai.getBoard().draw(window, tileSize, offsetAI, false);

        window.display();
    }

    // Ekran końcowy
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Nie udało się załadować czcionki\n";
        return;
    }

    sf::Text resultText;
    resultText.setFont(font);
    resultText.setString(playerWon ? "WYGRANA!" : "PRZEGRANA!");
    resultText.setCharacterSize(72);
    resultText.setFillColor(playerWon ? sf::Color::Green : sf::Color::Red);

    sf::FloatRect textRect = resultText.getLocalBounds();
    resultText.setOrigin(textRect.width / 2, textRect.height / 2);
    resultText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    bool endScreen = true;

    sf::Clock clock;
    while (endScreen && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                endScreen = false;
        }

        float time = clock.getElapsedTime().asSeconds();
        float scale = 1.0f + 0.05f * std::sin(time * 2.0f);
        resultText.setScale(scale, scale);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(resultText);
        window.display();
    }
}
