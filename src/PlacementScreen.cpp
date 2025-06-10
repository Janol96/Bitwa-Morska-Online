#include "PlacementScreen.h"
#include "BasicShip.h"

PlacementScreen::PlacementScreen(sf::Font& font, Player& player)
    : font(font), player(player), currentShipLength(4), currentOrientation(true) {}

void PlacementScreen::run(sf::RenderWindow& window) {
    float tileSize = 40.0f;
    sf::Vector2f offset(50, 50);
    bool running = true;

    while (running && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape && currentShipLength < 1)
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
                    }
                }
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int x = (mousePos.x - static_cast<int>(offset.x)) / static_cast<int>(tileSize);
        int y = (mousePos.y - static_cast<int>(offset.y)) / static_cast<int>(tileSize);
        ghostPosition = sf::Vector2i(x, y);

        window.clear(sf::Color::Black);
        player.getBoard().draw(window, tileSize, offset, true);

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
