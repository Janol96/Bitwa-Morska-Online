#include "SinglePlayerScreen.h"

class TestShip : public Ship {
public:
    TestShip(int length, sf::Vector2i pos, bool horizontal)
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

SinglePlayerScreen::SinglePlayerScreen(sf::Font& font) : board(10), font(font) {
    board.addShip(std::make_shared<TestShip>(4, sf::Vector2i(2, 3), true));
}

void SinglePlayerScreen::run(sf::RenderWindow& window) {
    bool running = true;
    while (running && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                running = false;
        }

        window.clear(sf::Color::Black);
        board.draw(window, 40.0f, sf::Vector2f(50, 50));
        window.display();
    }
}
