#include "SinglePlayerScreen.h"
#include "Game.h"
#include <memory>

// Lokalna implementacja testowego statku
class BasicShip : public Ship {
public:
    BasicShip(int length, sf::Vector2i pos, bool horizontal)
        : Ship(length, pos, horizontal) {}

    void draw(sf::RenderWindow& window, float tileSize, sf::Vector2f offset) const override {
        for (int i = 0; i < length; ++i) {
            int x = position.x + (horizontal ? i : 0);
            int y = position.y + (horizontal ? 0 : i);
            sf::RectangleShape shape(sf::Vector2f(tileSize - 2, tileSize - 2));
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
            window.draw(shape);
        }
    }
};

SinglePlayerScreen::SinglePlayerScreen(sf::Font& font)
    : font(font), player("Gracz"), currentShipLength(4), currentOrientation(true) {}

void SinglePlayerScreen::run(sf::RenderWindow& window) {
    float tileSize = 40.0f;
    sf::Vector2f offset(50, 50);
    bool running = true;

    while (running && window.isOpen()) {
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
                            // Uruchamiamy rozgrywkę jednoosobową
                            Game game(player);
                            game.run(window);
                            running = false;
                        }
                    }

                }
            }
        }

        // Aktualizacja ghosta (pozycja kursora)
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int x = (mousePos.x - static_cast<int>(offset.x)) / static_cast<int>(tileSize);
        int y = (mousePos.y - static_cast<int>(offset.y)) / static_cast<int>(tileSize);
        ghostPosition = sf::Vector2i(x, y);

        // Renderowanie
        window.clear(sf::Color::Black);
        player.getBoard().draw(window, tileSize, offset, true); // true – pokazuj statki gracza

        // Rysowanie ghost-mode
        if (ghostPosition.has_value()) {
            for (int i = 0; i < currentShipLength; ++i) {
                int gx = ghostPosition->x + (currentOrientation ? i : 0);
                int gy = ghostPosition->y + (currentOrientation ? 0 : i);

                sf::RectangleShape ghost(sf::Vector2f(tileSize - 2, tileSize - 2));
                ghost.setFillColor(sf::Color(150, 150, 150, 100)); // półprzezroczysty szary
                ghost.setPosition(offset.x + gx * tileSize, offset.y + gy * tileSize);
                window.draw(ghost);
            }
        }

        window.display();
    }
}
