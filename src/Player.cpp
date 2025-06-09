#include "Player.h"
#include "Ship.h"

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

Player::Player(const std::string& name) : board(10), name(name) {}

Board& Player::getBoard() {
    return board;
}

const Board& Player::getBoard() const {
    return board;
}

const std::string& Player::getName() const {
    return name;
}

void Player::placeShips() {
    board.addShip(std::make_shared<BasicShip>(4, sf::Vector2i(1, 1), true));
    board.addShip(std::make_shared<BasicShip>(3, sf::Vector2i(3, 4), false));
}

sf::Vector2i Player::chooseTarget() {
    return sf::Vector2i(0, 0); // do nadpisania w AI
}

void Player::notifyShotResult(bool /*hit*/) {
    // AI może się tu czegoś uczyć
}
