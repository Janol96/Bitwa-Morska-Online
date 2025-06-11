#include "SinglePlayerScreen.h"
#include "BasicShip.h"
#include "Game.h"
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

SinglePlayerScreen::SinglePlayerScreen(sf::Font& font)
    : font(font), player("Gracz"), currentShipLength(4), currentOrientation(true) {}

void SinglePlayerScreen::run(sf::RenderWindow& window) {
    float tileSize = 40.0f;
    sf::Vector2f offset(50, 50);
    bool running = true;

    // Ładowanie tła
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("menu_bg_clear.png")) {
        std::cerr << "Nie udało się załadować assets/menu_bg_clear.png\n";
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    while (running && window.isOpen()) {
        // Obsługa zdarzeń
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    running = false;
                else if (event.key.code == sf::Keyboard::R)
                    currentOrientation = !currentOrientation;
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {

                if (ghostPosition.has_value()) {
                    auto newShip = std::make_shared<BasicShip>(currentShipLength, *ghostPosition, currentOrientation);
                    if (player.getBoard().addShip(newShip)) {
                        currentShipLength--;
                        if (currentShipLength < 1) {
                            Game game(player);
                            game.run(window);
                            running = false;
                        }
                    }
                }
            }
        }

        // Aktualizacja ghost-mode (pozycja kursora)
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int x = (mousePos.x - static_cast<int>(offset.x)) / static_cast<int>(tileSize);
        int y = (mousePos.y - static_cast<int>(offset.y)) / static_cast<int>(tileSize);
        ghostPosition = sf::Vector2i(x, y);

        // RENDEROWANIE
        window.clear();

        // 1. Tło
        window.draw(backgroundSprite);

        // 2. Siatka
        for (int row = 0; row < 10; ++row) {
            for (int col = 0; col < 10; ++col) {
                sf::RectangleShape cell(sf::Vector2f(tileSize, tileSize));
                cell.setPosition(offset.x + col * tileSize, offset.y + row * tileSize);
                cell.setFillColor(sf::Color(128, 128, 128, 100));  // szare przezroczyste
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);
                window.draw(cell);
            }
        }

        // 3. Plansza gracza
        player.getBoard().draw(window, tileSize, offset, true);

        // 4. Ghost-mode
        if (ghostPosition.has_value()) {
            for (int i = 0; i < currentShipLength; ++i) {
                int gx = ghostPosition->x + (currentOrientation ? i : 0);
                int gy = ghostPosition->y + (currentOrientation ? 0 : i);

                sf::RectangleShape ghost(sf::Vector2f(tileSize - 2, tileSize - 2));
                ghost.setFillColor(sf::Color(150, 150, 150, 100));
                ghost.setPosition(offset.x + gx * tileSize, offset.y + gy * tileSize);
                window.draw(ghost);
            }
        }

        window.display();
    }
}
